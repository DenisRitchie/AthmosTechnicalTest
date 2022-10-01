#ifndef EFAB55F5_C152_4A9E_B50B_412E022731F3
#define EFAB55F5_C152_4A9E_B50B_412E022731F3

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Entities/User.hpp"
#include "Entities/Investor.hpp"

#include "Helpers/Convert.hpp"

#include <iostream>
#include <iomanip>

#include <any>
#include <variant>
#include <optional>
#include <functional>

#include <string>
#include <string_view>

#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

#include <ranges>

#include <boost/lexical_cast.hpp>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

using namespace EcosystemServices::Library::Entity;
using namespace EcosystemServices::Library::Helpers;

using std::literals::string_literals::     operator""s;
using std::literals::string_view_literals::operator""sv;

#define JSON(...) ::web::json::value::parse(U(#__VA_ARGS__))

enum class DummyEnum
{
  Value
};

struct DummyObject
{
    int32_t              Id;
    std::string          Name;
    bool                 Status;
    std::byte            Byte;
    DummyEnum            Enum;
    long double          Price;
    boost::uuids::uuid   UniqueId;
    std::vector<int32_t> Values;
};

REFL_AUTO(type(DummyObject), field(Id), field(Name), field(Status), field(Byte), field(Enum), field(Price), field(UniqueId), field(Values))

TEST(HelperConvertToObjectTests, JsonObjectToCppObject)
{
  // clang-format off
  auto json = JSON(
  {
    "Id": 2005,
    "UniqueId": "26af1c5e-5561-48b4-a9e4-8e8b216ecdf8",
    "Name": "Denis West",
    "Status": false,
    "Price": 45.365,
    "Byte": 255,
    "Enum": 0,
    "Values": [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
  });
  // clang-format on

  auto object = Convert::ToObject<DummyObject>(json);

  EXPECT_EQ(object.Id, 2005);
  EXPECT_EQ(object.Name, "Denis West"s);
  EXPECT_EQ(object.Status, false);
  EXPECT_EQ(object.Price, 45.365);
  EXPECT_EQ(object.Byte, std::byte{ 255 });
  EXPECT_EQ(object.Enum, DummyEnum::Value);
  EXPECT_EQ(boost::lexical_cast<std::string>(object.UniqueId), "26af1c5e-5561-48b4-a9e4-8e8b216ecdf8"s);
  EXPECT_EQ(object.Values.size(), 10);

  for ( int32_t index = 1; const auto& value : object.Values )
  {
    EXPECT_EQ(value, index++);
  }
}

TEST(HelperConvertToObjectTests, JsonArrayToCppObject)
{
  // clang-format off
  auto json = JSON(
  [
    {
      "Id": 2005,
      "UniqueId": "26af1c5e-5561-48b4-a9e4-8e8b216ecdf8",
      "Name": "Denis West",
      "Status": false,
      "Price": 45.365,
      "Byte": 255,
      "Enum": 0,
      "Values": [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    },
    {
      "Id": 2005,
      "UniqueId": "26af1c5e-5561-48b4-a9e4-8e8b216ecdf8",
      "Name": "Denis West",
      "Status": false,
      "Price": 45.365,
      "Byte": 255,
      "Enum": 0,
      "Values": [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    }
  ]);
  // clang-format on

  auto CheckValues = [&json]<typename TRange>()
  {
    auto values = Convert::ToObject<TRange>(json);
    EXPECT_EQ(values.size(), 2);

    for ( const auto& object : values )
    {
      EXPECT_EQ(object.Id, 2005);
      EXPECT_EQ(object.Name, "Denis West"s);
      EXPECT_EQ(object.Status, false);
      EXPECT_EQ(object.Price, 45.365);
      EXPECT_EQ(object.Byte, std::byte{ 255 });
      EXPECT_EQ(object.Enum, DummyEnum::Value);
      EXPECT_EQ(boost::lexical_cast<std::string>(object.UniqueId), "26af1c5e-5561-48b4-a9e4-8e8b216ecdf8"s);
      EXPECT_EQ(object.Values.size(), 10);

      for ( int32_t index = 1; const auto& value : object.Values )
      {
        EXPECT_EQ(value, index++);
      }
    }
  };

  CheckValues.operator()<std::list<DummyObject>>();
  CheckValues.operator()<std::deque<DummyObject>>();
  CheckValues.operator()<std::vector<DummyObject>>();
}

#endif /* EFAB55F5_C152_4A9E_B50B_412E022731F3 */
