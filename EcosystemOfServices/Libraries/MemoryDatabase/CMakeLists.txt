cmake_minimum_required(VERSION 3.24)

project(
  MemoryDatabase
  LANGUAGES C CXX
  VERSION 1.0.0.0
  DESCRIPTION "A header-only c++ library that provides in memory database json."
  HOMEPAGE_URL "https://github.com/DenisRitchie/AthmosTechnicalTest/tree/master/EcosystemOfServices/Libraries/MemoryJsonDatabase"
)

message(STATUS "${PROJECT_NAME} v${PROJECT_VERSION}: ${PROJECT_DESCRIPTION}")

add_library(MemoryDatabaseLibrary INTERFACE)
add_library(EcosystemServices::Library::MemoryDatabase ALIAS MemoryDatabaseLibrary)

target_sources(MemoryDatabaseLibrary INTERFACE MemoryJson.hpp)

target_link_libraries(MemoryDatabaseLibrary INTERFACE cpprestsdk::cpprest Boost::headers EcosystemServices::Library::Helpers)

target_compile_features(MemoryDatabaseLibrary INTERFACE cxx_std_20)

target_include_directories(MemoryDatabaseLibrary INTERFACE ${CMAKE_SOURCE_DIR}/Libraries)
