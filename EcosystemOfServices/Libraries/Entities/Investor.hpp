#ifndef BEE50156_E304_4C99_92D8_506EE2837F81
#define BEE50156_E304_4C99_92D8_506EE2837F81

#pragma once

#include <string>

#include <refl.hpp>

#include <boost/uuid/uuid.hpp>

namespace EcosystemServices::Library::Entity
{
  struct Investor
  {
      ::boost::uuids::uuid Id;
      ::std::string        Name;
      ::std::string        Email;
      ::std::string        Phone;
  };

} // namespace EcosystemServices::Library::Entity

// clang-format off

REFL_AUTO(
  type(EcosystemServices::Library::Entity::Investor),
  field(Id),
  field(Name),
  field(Email),
  field(Phone)
)

// clang-format on

#endif /* BEE50156_E304_4C99_92D8_506EE2837F81 */
