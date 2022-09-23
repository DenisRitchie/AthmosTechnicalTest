cmake_minimum_required(VERSION 3.24.1)

set(TEST_PROJECT_NAME MemoryDatabaseLibraryTests)

add_executable(${TEST_PROJECT_NAME} Main.cpp)

target_link_libraries(${TEST_PROJECT_NAME}
  PUBLIC
    GTest::gtest_main
    GTest::gmock_main
    EcosystemServices::Library::Helpers
    EcosystemServices::Library::Entities
    EcosystemServices::Library::MemoryDatabase
)

target_compile_features(${TEST_PROJECT_NAME} PUBLIC cxx_std_20)

# set_target_properties(${TEST_PROJECT_NAME}
#     PROPERTIES
#         RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Test"
# )

include(GoogleTest)
gtest_discover_tests(${TEST_PROJECT_NAME} TEST_PREFIX Library::MemoryDatabase)
