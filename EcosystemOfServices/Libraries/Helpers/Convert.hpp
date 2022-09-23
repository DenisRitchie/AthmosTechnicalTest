#ifndef E9CD3F60_E16A_4D63_811F_5D1F5934AD3F
#define E9CD3F60_E16A_4D63_811F_5D1F5934AD3F

#include "Concepts.hpp"

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

#include <cpprest/json.h>

namespace EcosystemServices::Library::Helpers
{
  class Convert final
  {
    public:
      inline static ::web::json::value ToJson(std::nullptr_t) noexcept
      {
        return ::web::json::value::null();
      }

      inline static ::web::json::value ToJson(const bool value) noexcept
      {
        return ::web::json::value::boolean(value);
      }

      inline static ::web::json::value ToJson(const std::byte value) noexcept
      {
        return ::web::json::value::number(std::to_integer<uint32_t>(value));
      }

      inline static ::web::json::value ToJson(const Enum auto value) noexcept
      {
        return ::web::json::value::number(static_cast<std::underlying_type_t<decltype(value)>>(value));
      }

      inline static ::web::json::value ToJson(const char value) noexcept
      {
        return ::web::json::value::number(value);
      }

      inline static ::web::json::value ToJson(const int8_t value) noexcept
      {
        return ::web::json::value::number(value);
      }

      inline static ::web::json::value ToJson(const uint8_t value) noexcept
      {
        return ::web::json::value::number(value);
      }

      inline static ::web::json::value ToJson(const int16_t value) noexcept
      {
        return ::web::json::value::number(value);
      }

      inline static ::web::json::value ToJson(const uint16_t value) noexcept
      {
        return ::web::json::value::number(value);
      }

      inline static ::web::json::value ToJson(const int32_t value) noexcept
      {
        return ::web::json::value::number(value);
      }

      inline static ::web::json::value ToJson(const uint32_t value) noexcept
      {
        return ::web::json::value::number(value);
      }

      inline static ::web::json::value ToJson(const long value) noexcept
      {
        return ::web::json::value::number(value);
      }

      inline static ::web::json::value ToJson(const unsigned long value) noexcept
      {
        return ::web::json::value::number(value);
      }

      inline static ::web::json::value ToJson(const long long value) noexcept
      {
        return ::web::json::value::number(static_cast<int64_t>(value));
      }

      inline static ::web::json::value ToJson(const unsigned long long value) noexcept
      {
        return ::web::json::value::number(static_cast<uint64_t>(value));
      }

      inline static ::web::json::value ToJson(const float value) noexcept
      {
        return ::web::json::value::number(value);
      }

      inline static ::web::json::value ToJson(const double value) noexcept
      {
        return ::web::json::value::number(value);
      }

      inline static ::web::json::value ToJson(const long double value) noexcept
      {
        return ::web::json::value::number(static_cast<double_t>(value));
      }

      inline static ::web::json::value ToJson(const char* value) noexcept
      {
        return ::web::json::value::string(value);
      }

      template <size_t Size>
      inline static ::web::json::value ToJson(const char (&value)[Size]) noexcept
      {
        return ::web::json::value::string(value);
      }

      inline static ::web::json::value ToJson(const std::string_view value) noexcept
      {
        return ::web::json::value::string({ value.cbegin(), value.cend() });
      }

      inline static ::web::json::value ToJson(const boost::uuids::uuid& uuid)
      {
        return ::web::json::value::string(boost::lexical_cast<std::string>(uuid));
      }

      // clang-format off
      template <Range TRange>
      requires NotEqualsTo<TRange, boost::uuids::uuid, std::string, std::string_view, std::wstring, std::wstring_view>
            && IsNotArray<TRange>::template Of<char, signed char, unsigned char, char8_t, char16_t, char32_t>
      inline static ::web::json::value ToJson(TRange&& values) noexcept // clang-format on
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
      inline static ::web::json::value ToJson(const TObject& value) noexcept // clang-format on
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
  };
} // namespace EcosystemServices::Library::Helpers

#endif /* E9CD3F60_E16A_4D63_811F_5D1F5934AD3F */
