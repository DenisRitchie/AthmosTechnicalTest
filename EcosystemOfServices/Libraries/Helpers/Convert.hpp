#ifndef E9CD3F60_E16A_4D63_811F_5D1F5934AD3F
#define E9CD3F60_E16A_4D63_811F_5D1F5934AD3F

#include "Concepts.hpp"

#include <type_traits>
#include <vector>
#include <string>
#include <string_view>
#include <exception>
#include <optional>
#include <any>

#include <refl.hpp>

#include <boost/lexical_cast.hpp>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include <cpprest/json.h>

namespace EcosystemServices::Library::Helpers
{
  class Convert final
  {
    public:
      [[nodiscard]] inline static ::web::json::value ToJson(std::nullptr_t) noexcept
      {
        return ::web::json::value::null();
      }

      [[nodiscard]] inline static ::web::json::value ToJson(const bool value) noexcept
      {
        return ::web::json::value::boolean(value);
      }

      [[nodiscard]] inline static ::web::json::value ToJson(const std::byte value) noexcept
      {
        return ::web::json::value::number(std::to_integer<uint32_t>(value));
      }

      [[nodiscard]] inline static ::web::json::value ToJson(const Enum auto value) noexcept
      {
        return ::web::json::value::number(static_cast<std::underlying_type_t<decltype(value)>>(value));
      }

      [[nodiscard]] inline static ::web::json::value ToJson(const char value) noexcept
      {
        return ::web::json::value::number(value);
      }

      [[nodiscard]] inline static ::web::json::value ToJson(const int8_t value) noexcept
      {
        return ::web::json::value::number(value);
      }

      [[nodiscard]] inline static ::web::json::value ToJson(const uint8_t value) noexcept
      {
        return ::web::json::value::number(value);
      }

      [[nodiscard]] inline static ::web::json::value ToJson(const int16_t value) noexcept
      {
        return ::web::json::value::number(value);
      }

      [[nodiscard]] inline static ::web::json::value ToJson(const uint16_t value) noexcept
      {
        return ::web::json::value::number(value);
      }

      [[nodiscard]] inline static ::web::json::value ToJson(const int32_t value) noexcept
      {
        return ::web::json::value::number(value);
      }

      [[nodiscard]] inline static ::web::json::value ToJson(const uint32_t value) noexcept
      {
        return ::web::json::value::number(value);
      }

      [[nodiscard]] inline static ::web::json::value ToJson(const long value) noexcept
      {
        return ::web::json::value::number(value);
      }

      [[nodiscard]] inline static ::web::json::value ToJson(const unsigned long value) noexcept
      {
        return ::web::json::value::number(value);
      }

      [[nodiscard]] inline static ::web::json::value ToJson(const long long value) noexcept
      {
        return ::web::json::value::number(static_cast<int64_t>(value));
      }

      [[nodiscard]] inline static ::web::json::value ToJson(const unsigned long long value) noexcept
      {
        return ::web::json::value::number(static_cast<uint64_t>(value));
      }

      [[nodiscard]] inline static ::web::json::value ToJson(const float value) noexcept
      {
        return ::web::json::value::number(value);
      }

      [[nodiscard]] inline static ::web::json::value ToJson(const double value) noexcept
      {
        return ::web::json::value::number(value);
      }

      [[nodiscard]] inline static ::web::json::value ToJson(const long double value) noexcept
      {
        return ::web::json::value::number(static_cast<double_t>(value));
      }

      [[nodiscard]] inline static ::web::json::value ToJson(const char* value) noexcept
      {
        return ::web::json::value::string(value);
      }

      template <size_t Size>
      [[nodiscard]] inline static ::web::json::value ToJson(const char (&value)[Size]) noexcept
      {
        return ::web::json::value::string(value);
      }

      [[nodiscard]] inline static ::web::json::value ToJson(const std::string_view value) noexcept
      {
        return ::web::json::value::string({ value.cbegin(), value.cend() });
      }

      [[nodiscard]] inline static ::web::json::value ToJson(const boost::uuids::uuid& uuid)
      {
        return ::web::json::value::string(boost::lexical_cast<std::string>(uuid));
      }

      // clang-format off
      template <Range TRange>
      requires NotEqualsTo<TRange, boost::uuids::uuid, std::string, std::string_view, std::wstring, std::wstring_view>
            && IsNotArray<TRange>::template Of<char, signed char, unsigned char, char8_t, char16_t, char32_t>
      [[nodiscard]] inline static ::web::json::value ToJson(TRange&& values) noexcept // clang-format on
      {
        auto json_values = ::web::json::value::array(std::ranges::size(values));

        for ( size_t index = 0; const auto& value : values )
        {
          json_values[index++] = ToJson(value);
        }

        return json_values;
      }

      // clang-format off
      template <ReflectObject TObject>
      requires NotCollection<TObject> and NotArithmetic<TObject> and NotPointer<TObject>
      [[nodiscard]] inline static ::web::json::value ToJson(const TObject& value) noexcept // clang-format on
      {
        using reflect_t    = refl::type_descriptor<std::remove_cvref_t<decltype(value)>>;
        using object_key_t = std::vector<std::pair<utility::string_t, ::web::json::value>>;

        object_key_t properties;
        reflect_t    reflect_value = refl::reflect(value);

        for_each(
            reflect_value.members,
            [&](const auto member, [[maybe_unused]] auto index /*get_member_index(member);*/)
            {
              if constexpr ( is_readable(member) && is_field(member) )
              {
                properties.emplace_back(get_display_name(member), ToJson(member(value)));
              }
            }
        );

        return ::web::json::value::object(properties);
      }

      template <typename TValue>
      inline static TValue ToObject(const ::web::json::value& json)
      {
        return JsonToObject<TValue>(json);
      }

    private:
      template <typename TValue>
      inline static TValue JsonToObject(const ::web::json::value& json) requires std::same_as<std::string, TValue>
      {
        return json.as_string();
      }

      template <typename TValue>
      inline static TValue JsonToObject(const ::web::json::value& json) requires std::same_as<boost::uuids::uuid, TValue>
      {
        boost::uuids::string_generator generator;
        return generator(json.as_string());
      }

      template <template <typename> typename TOptional, typename TValue>
      inline static std::optional<TValue> JsonToObject(const ::web::json::value& json) requires std::same_as<std::optional<TValue>, TOptional<TValue>>
      {
        if ( json.is_null() )
        {
          return std::nullopt;
        }
        else
        {
          return JsonToObject<TValue>(json);
        }
      }

      template <Enum TValue>
      inline static TValue JsonToObject(const ::web::json::value& json)
      {
        return static_cast<TValue>(JsonToObject<std::underlying_type_t<TValue>>(json));
      }

      template <Arithmetic TValue>
      inline static TValue JsonToObject(const ::web::json::value& json)
      {
        if ( json.is_boolean() )
        {
          return static_cast<TValue>(json.as_bool());
        }

        const ::web::json::number& json_number = json.as_number();

        if ( json_number.is_integral() )
        {
          if ( json_number.is_int64() )
          {
            return static_cast<TValue>(json_number.to_int64());
          }
          else
          {
            return static_cast<TValue>(json_number.to_uint64());
          }
        }

        return static_cast<TValue>(json_number.to_double());
      }

      // clang-format off
      template <SequenceContainer TRange>
      requires NotEqualsTo<TRange, boost::uuids::uuid, std::string, std::string_view, std::wstring, std::wstring_view>
            && IsNotArray<TRange>::template Of<char, signed char, unsigned char, char8_t, char16_t, char32_t>
      inline static TRange JsonToObject(const ::web::json::value& json) // clang-format on
      {
        TRange range{};

        for ( const auto& value : json.as_array() )
        {
          range.push_back(JsonToObject<typename TRange::value_type>(value));
        }

        return range;
      }

      // clang-format off
      template <ReflectObject TObject>
      requires NotCollection<TObject> and NotArithmetic<TObject> and NotPointer<TObject>
      inline static TObject JsonToObject(const ::web::json::value& json) // clang-format on
      {
        using reflect_t = refl::type_descriptor<std::remove_cvref_t<TObject>>;

        TObject   object_result{};
        reflect_t reflect_value = refl::reflect(object_result);

        for_each(
            reflect_value.members,
            [&](const auto member, [[maybe_unused]] auto index /*get_member_index(member);*/)
            {
              if constexpr ( is_writable(member) && is_field(member) )
              {
                using member_t        = std::remove_cvref_t<decltype(member(object_result))>;

                auto&& json_value     = json.at(get_display_name(member));
                member(object_result) = JsonToObject<member_t>(json_value);
              }
            }
        );

        return object_result;
      }
  };
} // namespace EcosystemServices::Library::Helpers

#endif /* E9CD3F60_E16A_4D63_811F_5D1F5934AD3F */
