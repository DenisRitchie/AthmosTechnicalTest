cmake_minimum_required(VERSION 3.24)

project(
    ListInvertersService
    LANGUAGES C CXX
    VERSION 1.0.0.0
    DESCRIPTION "ListInverters MicroService"
    HOMEPAGE_URL "https://github.com/DenisRitchie/AthmosTechnicalTest/tree/master/EcosystemOfServices/Services/ListInvertersService"
)

message(STATUS "${PROJECT_NAME} v${PROJECT_VERSION}: ${PROJECT_DESCRIPTION}")

add_executable(${PROJECT_NAME} Main.cpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${_external_library_boost}
        ${_external_library_common}
        EcosystemServices::Library::Helpers
        EcosystemServices::Library::Entities
)
