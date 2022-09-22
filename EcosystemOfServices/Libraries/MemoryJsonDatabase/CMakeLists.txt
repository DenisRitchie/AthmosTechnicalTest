cmake_minimum_required(VERSION 3.24)

project(
  MemoryJsonDatabase
  LANGUAGES C CXX
  VERSION 1.0.0.0
  DESCRIPTION "A header-only c++ library that provides in memory database json."
  HOMEPAGE_URL "https://github.com/DenisRitchie/AthmosTechnicalTest/tree/master/EcosystemOfServices/Libraries/Entities"
)

message(STATUS "${PROJECT_NAME} v${PROJECT_VERSION}: ${PROJECT_DESCRIPTION}")

add_library(MemoryJsonDatabaseLibrary INTERFACE)
add_library(EcosystemServices::Library::MemoryJsonDatabase ALIAS MemoryJsonDatabaseLibrary)

target_sources(MemoryJsonDatabaseLibrary INTERFACE MemDbJson.hpp)

target_link_libraries(MemoryJsonDatabaseLibrary INTERFACE cpprestsdk::cpprest Boost::headers)

target_compile_features(MemoryJsonDatabaseLibrary INTERFACE cxx_std_20)

target_include_directories(MemoryJsonDatabaseLibrary INTERFACE ${CMAKE_SOURCE_DIR}/Libraries)
