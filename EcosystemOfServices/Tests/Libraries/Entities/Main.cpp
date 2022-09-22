// https://google.github.io/googletest/reference/testing.html

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <concepts>
#include <iterator>
#include <algorithm>

#include <boost/lexical_cast.hpp>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include <refl.hpp>

#include "Entities/User.hpp"
#include "Entities/Investor.hpp"

using namespace EcosystemServices::Library;

TEST(ReflectableObjectTest, ReflectEntity)
{
  EXPECT_TRUE((std::same_as<decltype(Entity::User::Id), boost::uuids::uuid> && refl::trait::is_reflectable_v<Entity::User>));
  EXPECT_TRUE((std::same_as<decltype(Entity::Investor::Id), boost::uuids::uuid> && refl::trait::is_reflectable_v<Entity::Investor>));
}

TEST(ReflectableObjectTest, UserEntity)
{
  EcosystemServices::Library::Entity::User user =         //
      {                                                   //
        .Id       = ::boost::uuids::random_generator()(), //
        .UserName = "Denis",
        .Password = "Password"
      };

  constexpr refl::type_descriptor<Entity::User> type = refl::reflect<Entity::User>();

  EXPECT_STREQ(type.name.c_str(), "EcosystemServices::Library::Entity::User");
  EXPECT_EQ(type.declared_members.size, 3);

  // iterate over the members of T
  for_each(
      type.members,
      [&](const auto member)
      {
        // is_readable checks if the member is a non-const field
        // or a 0-arg const-qualified function marked with property attribute
        if constexpr ( is_readable(member) )
        {
          // get_display_name prefers the friendly_name of the property over the function name
          printf("%s = ", get_display_name(member));

          // member(value) returns a reference to the field or calls the property accessor
          std::cout << member(user) << "\n";
        }
      }
  );
}

TEST(ReflectableObjectTest, InvestorEntity)
{
  EXPECT_STREQ(
      refl::descriptor::get_name(refl::reflect<Entity::Investor>()).c_str(), //
      "EcosystemServices::Library::Entity::Investor"
  );

  EXPECT_EQ(refl::member_list<Entity::Investor>::size, 4);

  EXPECT_STREQ(refl::descriptor::get_name(refl::trait::get_t<0, refl::member_list<Entity::Investor>>{}).c_str(), "Id");
  EXPECT_STREQ(refl::descriptor::get_name(refl::trait::get_t<1, refl::member_list<Entity::Investor>>{}).c_str(), "Name");
  EXPECT_STREQ(refl::descriptor::get_name(refl::trait::get_t<2, refl::member_list<Entity::Investor>>{}).c_str(), "Email");
  EXPECT_STREQ(refl::descriptor::get_name(refl::trait::get_t<3, refl::member_list<Entity::Investor>>{}).c_str(), "Phone");
}

auto main(int32_t argc, char** argv) -> int32_t
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
