#ifndef CA95701E_5A3F_42CB_AE84_0D810AE6AC92
#define CA95701E_5A3F_42CB_AE84_0D810AE6AC92

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Entities/User.hpp"
#include "Entities/Investor.hpp"

#include "Helpers/Convert.hpp"

#include <string_view>

#include <boost/uuid/uuid_generators.hpp>

using namespace EcosystemServices::Library::Entity;
using namespace EcosystemServices::Library::Helpers;

using std::literals::string_literals::     operator""s;
using std::literals::string_view_literals::operator""sv;

TEST(HelperConvertToJsonTests, BooleanConvertToJson)
{
  auto value = Convert::ToJson(true);
  EXPECT_TRUE(value.is_boolean());
  EXPECT_TRUE(value.as_bool());
  EXPECT_EQ(value.serialize(), "true"s);

  value = Convert::ToJson(false);
  EXPECT_TRUE(value.is_boolean());
  EXPECT_FALSE(value.as_bool());
  EXPECT_EQ(value.serialize(), "false"s);
}

TEST(HelperConvertToJsonTests, CharPointerConvertToJson)
{
  constexpr const char raw_string[]        = "Raw String";
  const char*          pointer_string      = "Pointer String";

  auto                 json_raw_string1    = Convert::ToJson("Raw String");
  auto                 json_raw_string2    = Convert::ToJson(raw_string);
  auto                 json_pointer_string = Convert::ToJson(pointer_string);

  EXPECT_TRUE(json_raw_string1.is_string());
  EXPECT_TRUE(json_raw_string2.is_string());
  EXPECT_TRUE(json_pointer_string.is_string());

  EXPECT_EQ(json_raw_string1.as_string(), "Raw String"s);
  EXPECT_EQ(json_raw_string2.as_string(), std::string(raw_string));
  EXPECT_EQ(json_pointer_string.as_string(), std::string(pointer_string));
}

TEST(HelperConvertToJsonTests, StringConvertToJson)
{
  auto json_string = Convert::ToJson("String"s);

  EXPECT_TRUE(json_string.is_string());
  EXPECT_EQ(json_string.as_string(), "String"s);
}

TEST(HelperConvertToJsonTests, StringViewConvertToJson)
{
  auto json_string = Convert::ToJson("StringView"sv);

  EXPECT_TRUE(json_string.is_string());
  EXPECT_EQ(json_string.as_string(), "StringView"sv);
}

TEST(HelperConvertToJsonTests, NumberConvertToJson)
{
  auto json_char_value          = Convert::ToJson('A');
  auto json_signed_char_value   = Convert::ToJson(int8_t('A'));
  auto json_unsigned_char_value = Convert::ToJson(uint8_t('A'));
  auto json_short_value         = Convert::ToJson(int16_t(-1));
  auto json_ushort_value        = Convert::ToJson(uint16_t(1));
  auto json_int_value           = Convert::ToJson(int32_t(-1));
  auto json_uint_value          = Convert::ToJson(uint32_t(1));
  auto json_long_value          = Convert::ToJson(static_cast<long>(-1));
  auto json_ulong_value         = Convert::ToJson(static_cast<unsigned long>(1));
  auto json_long_long_value     = Convert::ToJson(static_cast<long long>(-1));
  auto json_ulong_long_value    = Convert::ToJson(static_cast<unsigned long long>(1));
  auto json_float_value         = Convert::ToJson(10.0F);
  auto json_double_value        = Convert::ToJson(10.0);
  auto json_long_double_value   = Convert::ToJson(10.0L);

  EXPECT_TRUE(json_char_value.is_integer());
  EXPECT_TRUE(json_signed_char_value.is_integer() and json_signed_char_value.as_number().is_int32());
  EXPECT_TRUE(json_unsigned_char_value.is_integer() and json_unsigned_char_value.as_number().is_uint32());
  EXPECT_TRUE(json_short_value.is_integer() and json_short_value.as_number().is_int32());
  EXPECT_TRUE(json_ushort_value.is_integer() and json_ushort_value.as_number().is_uint32());
  EXPECT_TRUE(json_int_value.is_integer());
  EXPECT_TRUE(json_uint_value.is_integer());
  EXPECT_TRUE(json_long_value.is_integer() and json_long_value.as_number().is_int64());
  EXPECT_TRUE(json_ulong_value.is_integer() and json_ulong_value.as_number().is_uint64());
  EXPECT_TRUE(json_long_long_value.is_integer() and json_long_long_value.as_number().is_int64());
  EXPECT_TRUE(json_ulong_long_value.is_integer() and json_ulong_long_value.as_number().is_uint64());
  EXPECT_TRUE(json_float_value.is_double());
  EXPECT_TRUE(json_double_value.is_double());
  EXPECT_TRUE(json_long_double_value.is_double());
}

TEST(HelperConvertToJsonTests, EnumConvertToJson)
{
  enum EnumWithoutScope
  {
    ValueWithoutScope = 15
  };

  enum class EnumWithScope
  {
    Value = 30
  };

  auto json_byte_value  = Convert::ToJson(std::byte{ 1 });
  auto json_enum_value1 = Convert::ToJson(ValueWithoutScope);
  auto json_enum_value2 = Convert::ToJson(EnumWithScope::Value);

  EXPECT_TRUE(json_byte_value.is_number());
  EXPECT_TRUE(json_enum_value1.is_number());
  EXPECT_TRUE(json_enum_value2.is_number());

  EXPECT_EQ(std::byte{ 1 }, std::byte(json_byte_value.as_number().to_uint32()));
  EXPECT_EQ(ValueWithoutScope, json_enum_value1.as_number().to_uint32());
  EXPECT_EQ(EnumWithScope::Value, EnumWithScope(json_enum_value2.as_number().to_uint32()));
}

TEST(HelperConvertToJsonTests, ArrayConvertToJson)
{
  // clang-format off
  std::array<User, 5> users =
  {
    User
    {
      .Id       = boost::uuids::random_generator()(),
      .UserName = "Denis West",
      .Password = "Contraseña"
    },
    User
    {
      .Id       = boost::uuids::random_generator()(),
      .UserName = "Jeremy Fonseca",
      .Password = "Contraseña"
    },
    User
    {
      .Id       = boost::uuids::random_generator()(),
      .UserName = "Raúl Campesino",
      .Password = "Contraseña"
    },
    User
    {
      .Id       = boost::uuids::random_generator()(),
      .UserName = "Modesto Hilario",
      .Password = "Contraseña"
    },
    User
    {
      .Id       = boost::uuids::random_generator()(),
      .UserName = "Haywill Mariano",
      .Password = "Contraseña"
    }
  };
  // clang-format on

  auto json_array = Convert::ToJson(users);
  printf("Json: %s", json_array.serialize().c_str());

  EXPECT_TRUE(json_array.is_array());
  EXPECT_EQ(json_array.size(), users.size());
  EXPECT_EQ(json_array[4].as_object()["UserName"].as_string(), users[4].UserName);
  EXPECT_EQ(json_array[3]["Id"].as_string(), boost::lexical_cast<std::string>(users[3].Id));
}

TEST(HelperConvertToJsonTests, Array2ConvertToJson)
{
  // clang-format off
  User users[] =
  {
    User
    {
      .Id       = boost::uuids::random_generator()(),
      .UserName = "Denis West",
      .Password = "Contraseña"
    },
    User
    {
      .Id       = boost::uuids::random_generator()(),
      .UserName = "Jeremy Fonseca",
      .Password = "Contraseña"
    }
  };
  // clang-format on

  auto json_array = Convert::ToJson(users);
  printf("Json: %s", json_array.serialize().c_str());

  EXPECT_TRUE(json_array.is_array());
  EXPECT_EQ(json_array.size(), std::size(users));
  EXPECT_EQ(json_array[0].as_object()["UserName"].as_string(), users[0].UserName);
  EXPECT_EQ(json_array[1]["Id"].as_string(), boost::lexical_cast<std::string>(users[1].Id));
}

TEST(HelperConvertToJsonTests, ObjectConvertToJson)
{
  Investor investor = {
    .Id    = boost::uuids::random_generator()(), //
    .Name  = "Denis West",                       //
    .Email = "DenisWest@outlook.com",            //
    .Phone = "+505 8660-9518"                    //
  };

  static_assert(ReflectObject<decltype(investor)> and NotArithmetic<decltype(investor)> and NotCollection<decltype(investor)> and NotPointer<decltype(investor)>);

  auto json_object = Convert::ToJson(investor);
  printf("Json: %s", json_object.serialize().c_str());

  EXPECT_TRUE(json_object.is_object());
  EXPECT_EQ(json_object["Id"].as_string(), boost::uuids::to_string(investor.Id));
  EXPECT_EQ(json_object["Name"].as_string(), investor.Name);
  EXPECT_EQ(json_object["Email"].as_string(), investor.Email);
  EXPECT_EQ(json_object["Phone"].as_string(), investor.Phone);
}

#endif /* CA95701E_5A3F_42CB_AE84_0D810AE6AC92 */
