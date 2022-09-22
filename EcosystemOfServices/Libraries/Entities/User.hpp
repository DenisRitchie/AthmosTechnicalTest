#ifndef B2EAFD7C_976A_4E36_AE0F_8A2B3E2734E5
#define B2EAFD7C_976A_4E36_AE0F_8A2B3E2734E5

#pragma once

#include <string>

#include <refl.hpp>

#include <boost/uuid/uuid.hpp>

namespace EcosystemServices::Library::Entity
{
  struct User
  {
      ::boost::uuids::uuid Id;
      ::std::string        UserName;
      ::std::string        Password;
  };
} // namespace EcosystemServices::Library::Entity

// clang-format off

REFL_AUTO(
  type(EcosystemServices::Library::Entity::User),
  field(Id),
  field(UserName),
  field(Password)
)

// clang-format on

#endif /* B2EAFD7C_976A_4E36_AE0F_8A2B3E2734E5 */
