#ifndef FECCEC6A_3C23_4F61_9F6C_7CDCDB7B0B33
#define FECCEC6A_3C23_4F61_9F6C_7CDCDB7B0B33

#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <type_traits>
#include <concepts>

#include <cpprest/json.h>

#include <boost/lexical_cast.hpp>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "Helpers/Convert.hpp"

namespace EcosystemServices::Library::MemoryDatabase
{
  class MemoryJson
  {
    public:
      MemoryJson()
        : m_Database{ ::web::json::value::array() }
      {
      }

      MemoryJson(const std::filesystem::path& path)
        : MemoryJson{}
      {
        if ( std::filesystem::exists(path) )
        {
          std::ifstream json_file{ path.c_str(), std::ios::out | std::ios::in };
          m_Database = ::web::json::value::parse(json_file);
        }
      }

      boost::uuids::uuid Insert(EcosystemServices::Library::Helpers::ReflectObject auto&& object) noexcept
      {
        object.Id = boost::uuids::random_generator()();
        return object.Id;
      }

    private:
      ::web::json::value m_Database;
  };
} // namespace EcosystemServices::Library::MemoryDatabase

#endif /* FECCEC6A_3C23_4F61_9F6C_7CDCDB7B0B33 */
