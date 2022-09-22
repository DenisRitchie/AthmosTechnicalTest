cmake_minimum_required(VERSION 3.24)

project(
    EntitiesLibrary
    LANGUAGES C CXX
    VERSION 1.0.0.0
    DESCRIPTION "A header-only c++ library that provides entity types."
    HOMEPAGE_URL "https://github.com/DenisRitchie/AthmosTechnicalTest/tree/master/EcosystemOfServices/Libraries/Entities"
)

message(STATUS "${PROJECT_NAME} v${PROJECT_VERSION}: ${PROJECT_DESCRIPTION}")

add_library(EntitiesLibrary INTERFACE)
add_library(EcosystemServices::Library::Entities ALIAS EntitiesLibrary)

target_sources(EntitiesLibrary INTERFACE User.hpp Investor.hpp)

target_link_libraries(EntitiesLibrary INTERFACE Boost::headers)

target_compile_features(EntitiesLibrary INTERFACE cxx_std_20)

target_include_directories(EntitiesLibrary INTERFACE ${CMAKE_SOURCE_DIR}/Libraries)
