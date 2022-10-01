#ifndef C809D3A4_6BD7_4B37_A1F2_E98785194D73
#define C809D3A4_6BD7_4B37_A1F2_E98785194D73

// https://en.cppreference.com/w/cpp/ranges/range

#include <tuple>
#include <ranges>
#include <concepts>
#include <type_traits>

#include <refl.hpp>
#include <boost/uuid/uuid.hpp>

namespace EcosystemServices::Library::Helpers
{
  template <typename TValue>
  concept Arithmetic = std::is_arithmetic_v<TValue>;

  template <typename TValue>
  concept NotArithmetic = not Arithmetic<TValue>;

  template <typename TValue>
  concept NotPointer = not std::is_pointer_v<TValue>;

  template <typename TValue>
  concept Enum = std::is_enum_v<TValue>;

  template <typename TObject>
  concept ReflectObject = refl::trait::is_reflectable_v<TObject> && std::is_class_v<TObject>;

  template <typename TRange>
  concept Range = std::ranges::range<TRange>;

  template <typename TypeToCheck, typename... TypesToCheckAgainst>
  concept EqualsTo = (std::is_same_v<std::remove_cvref_t<TypeToCheck>, TypesToCheckAgainst> || ...);

  template <typename TypeToCheck, typename... TypesToCheckAgainst>
  concept NotEqualsTo = (std::negation_v<std::is_same<std::remove_cvref_t<TypeToCheck>, TypesToCheckAgainst>> && ...);

  template <typename TRange>
  concept NotCollection = not Range<TRange>;

  template <class... T>
  constexpr bool AlwaysFalse = false;

  template <class TObject>
  struct IsArray
  {
      using ArrayType                   = std::remove_extent_t<std::remove_cvref_t<TObject>>;
      static constexpr const bool Value = std::is_array_v<TObject>;

      template <class... TArgs>
      static constexpr const bool Of = std::disjunction_v<std::is_same<ArrayType, TArgs>...>;
  };

  template <class TObject>
  struct IsNotArray
  {
      using ArrayType                   = typename IsArray<TObject>::ArrayType;
      static constexpr const bool Value = not IsArray<TObject>::Value;

      template <class... TArgs>
      static constexpr const bool Of = not IsArray<TObject>::template Of<TArgs...>;
  };

  namespace Detail
  {
    // https://en.cppreference.com/w/cpp/types/is_scoped_enum
    // https://gcc.gnu.org/onlinedocs/gcc/Diagnostic-Pragmas.html
    // https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html

    namespace // avoid ODR violation
    {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"

      template <typename T>
      auto TestSizable(int32_t) -> decltype(sizeof(T), std::true_type{});

      template <typename>
      auto TestSizable(...) -> std::false_type;

      template <typename T>
      auto TestNonConvertibleToInt(int32_t) -> decltype(static_cast<std::false_type (*)(int32_t)>(nullptr)(std::declval<T>()));

      template <typename>
      auto TestNonConvertibleToInt(...) -> std::true_type;

      template <typename T>
      inline constexpr bool IsScopedEnumImpl = std::conjunction_v<decltype(TestSizable<T>(0)), decltype(TestNonConvertibleToInt<T>(0))>;

#pragma GCC diagnostic pop
    } // namespace
  }   // namespace Detail

  template <typename>
  struct IsScopedEnum : std::false_type
  {
  };

  template <Enum T>
  struct IsScopedEnum<T> : std::bool_constant<Detail::IsScopedEnumImpl<T>>
  {
  };

  template <class T>
  inline constexpr bool IsScopedEnumV = IsScopedEnum<T>::value;

  template <typename TValue>
  concept ScopedEnum = IsScopedEnumV<TValue>;

  // https://cpprefjp.github.io/lang/cpp20/concepts.html
  // clang-format off

  template <class TRange>
  concept SequenceContainer = requires(TRange Range)
  {
    typename TRange::size_type;
    typename TRange::value_type;

    { Range.size()     } -> std::convertible_to<typename TRange::size_type>;
    { std::size(Range) } -> std::convertible_to<typename TRange::size_type>;

    Range.push_back(std::declval<typename TRange::value_type>());
  };

  // clang-format on

  // helper type for the visitor or others
  template <class... Ts>
  struct Overloaded : Ts...
  {
      using Ts::operator()...;
  };

  // explicit deduction guide (not needed as of C++20)
  template <class... Ts>
  Overloaded(Ts...) -> Overloaded<Ts...>;

} // namespace EcosystemServices::Library::Helpers

#endif /* C809D3A4_6BD7_4B37_A1F2_E98785194D73 */
