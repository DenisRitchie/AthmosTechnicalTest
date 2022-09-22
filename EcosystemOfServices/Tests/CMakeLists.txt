cmake_minimum_required(VERSION 3.24.1)

project(EcosystemServicesTest
  LANGUAGES C CXX
  VERSION 1.0.0.0
  DESCRIPTION "Ecosystem Services Unit Tests"
  HOMEPAGE_URL "https://github.com/Magudali-Marketplace/magudali-marketplace-core"
)

message(STATUS "${PROJECT_NAME} v${PROJECT_VERSION}: ${PROJECT_DESCRIPTION}")

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_subdirectory(Services)
add_subdirectory(Libraries)
