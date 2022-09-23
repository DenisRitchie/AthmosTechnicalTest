cmake_minimum_required(VERSION 3.24)

project(
    HelpersLibrary
    LANGUAGES C CXX
    VERSION 1.0.0.0
    DESCRIPTION "A header-only c++ library that provides helpers classes and functions."
    HOMEPAGE_URL "https://github.com/DenisRitchie/AthmosTechnicalTest/tree/master/EcosystemOfServices/Libraries/Helpers"
)

message(STATUS "${PROJECT_NAME} v${PROJECT_VERSION}: ${PROJECT_DESCRIPTION}")

add_library(HelpersLibrary INTERFACE)
add_library(EcosystemServices::Library::Helpers ALIAS HelpersLibrary)

target_sources(HelpersLibrary INTERFACE Convert.hpp Concepts.hpp)

target_link_libraries(HelpersLibrary INTERFACE Boost::headers cpprestsdk::cpprest)

target_compile_features(HelpersLibrary INTERFACE cxx_std_20)

target_include_directories(HelpersLibrary INTERFACE ${CMAKE_SOURCE_DIR}/Libraries)
