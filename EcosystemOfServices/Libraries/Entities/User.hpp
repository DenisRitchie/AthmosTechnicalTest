#define __LIBRARY_ENTITIES_INVESTOR_HPP__
#define __LIBRARY_ENTITIES_INVESTOR_HPP__

#pragma once

#include <string>

namespace EcosystemServices::Library::Entity
{
  struct User
  {
      std::string Id;
      std::string UserName;
      std::string Password;
  };
}

#endif