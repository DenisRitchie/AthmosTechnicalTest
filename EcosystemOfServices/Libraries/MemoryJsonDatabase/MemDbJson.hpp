#ifndef FECCEC6A_3C23_4F61_9F6C_7CDCDB7B0B33
#define FECCEC6A_3C23_4F61_9F6C_7CDCDB7B0B33

#pragma once

#include <string>
#include <sstream>
#include <tuple>
#include <optional>
#include <variant>
#include <filesystem>
#include <type_traits>
#include <concepts>

#include <cpprest/json.h>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include <refl.hpp>

namespace EcosystemServices::Library::MemoryJsonDatabase
{
  namespace Detail
  {
    template <typename TObject>
    concept JValue =
        ::std::same_as<decltype(TObject::Id), ::boost::uuids::uuid> && refl::trait::is_reflectable_v<TObject>;
  } // namespace Detail

  class MemoryJsonDatabase
  {
    public:
      MemoryJsonDatabase()
        : m_Database{ ::web::json::value::array() }
      {
      }

      MemoryJsonDatabase(const ::std::filesystem::path& path)
        : MemoryJsonDatabase()
      {
        if ( ::std::filesystem::exists(path) )
        {
          ::std::ifstream json_file{ path.c_str(), ::std::ios::out | ::std::ios::in };
          m_Database = ::web::json::value::parse(json_file);
        }
      }

      template <Detail::JValue TObject>
      ::boost::uuids::uuid Insert(const TObject& object) noexcept
      {
        return {};
      }

    private:
      ::web::json::value m_Database;
  };
} // namespace EcosystemServices::Library::MemoryJsonDatabase

#endif /* FECCEC6A_3C23_4F61_9F6C_7CDCDB7B0B33 */
