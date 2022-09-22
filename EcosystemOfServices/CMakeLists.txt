cmake_minimum_required(VERSION 3.24)

project(
    EcosystemServices
    LANGUAGES C CXX
    VERSION 1.0.0.0
    DESCRIPTION "Series of microservices in charge of managing the information of some investors"
    HOMEPAGE_URL "https://github.com/DenisRitchie/AthmosTechnicalTest/tree/master/EcosystemOfServices"
)

message(STATUS "Project: ${PROJECT_NAME} Version: ${PROJECT_VERSION}")

add_compile_options(-Wall -Wextra -pedantic -Werror -fstrict-enums -fconcepts -fcoroutines -fpermissive)

set(Boost_NO_WARN_NEW_VERSIONS ON)

find_package(Boost 1.80.0 REQUIRED COMPONENTS thread context coroutine filesystem iostreams chrono atomic random system date_time regex)
find_package(ut CONFIG REQUIRED)

list(APPEND _external_library_boost
  Boost::headers
  Boost::thread
  Boost::context
  Boost::coroutine
  Boost::filesystem
  Boost::iostreams
  Boost::chrono
  Boost::atomic
  Boost::random
  Boost::system
  Boost::date_time
  Boost::regex
  Boost::ut
)

find_package(cpprestsdk CONFIG REQUIRED)
find_package(benchmark CONFIG REQUIRED)
find_package(cpp-jwt CONFIG REQUIRED)
find_package(tinyxml2 CONFIG REQUIRED)
find_package(unofficial-libharu CONFIG REQUIRED)
find_package(log4cplus CONFIG REQUIRED)
find_package(microsoft-signalr CONFIG REQUIRED)

list(APPEND _external_library_common
  cpprestsdk::cpprest
  benchmark::benchmark
  benchmark::benchmark_main
  cpp-jwt::cpp-jwt
  tinyxml2::tinyxml2
  unofficial::libharu::haru
  log4cplus::log4cplus
  microsoft-signalr::microsoft-signalr
)

find_path(JWT_CPP_INCLUDE_DIRS "jwt-cpp/base.h")
find_path(REFL_CPP_INCLUDE_DIRS "refl.hpp")
find_path(BEXT_DI_INCLUDE_DIRS "boost/di.hpp")
find_path(BEXT_SML_INCLUDE_DIRS "boost/sml.hpp")

include_directories(${JWT_CPP_INCLUDE_DIRS})
include_directories(${REFL_CPP_INCLUDE_DIRS})
include_directories(${BEXT_DI_INCLUDE_DIRS})
include_directories(${BEXT_SML_INCLUDE_DIRS})

add_subdirectory(Libraries)
add_subdirectory(Services)
add_subdirectory(Tests)
