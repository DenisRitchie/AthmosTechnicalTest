#define __LIBRARY_ENTITIES_INVESTOR_HPP__
#define __LIBRARY_ENTITIES_INVESTOR_HPP__

#pragma once

#include <string>

namespace EcosystemServices::Library::Entity
{
  struct Investor
  {
      std::string Id;
      std::string Name;
      std::string Email;
      std::string Phone;
  };
}

#endif
