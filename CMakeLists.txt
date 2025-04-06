cmake_minimum_required(VERSION 3.14)
project(ollama_drogon)

set(CMAKE_CXX_STANDARD 17)
set(FETCHCONTENT_QUIET OFF)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

find_package(Drogon REQUIRED)

include_directories(
    ${PROJECT_SOURCE_DIR}/controller
    ${PROJECT_SOURCE_DIR}/service
)

file(GLOB CONTROLLERS "controller/*.cpp")
file(GLOB SERVICES "service/*.cpp")

add_executable(${PROJECT_NAME}
    main.cpp
    ${CONTROLLERS}
    ${SERVICES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon jsoncpp_lib)


# Catch2 for unit tests
#find_package(Catch2 REQUIRED)
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)

find_package(jsoncpp REQUIRED)

add_executable(test_ollama_service
    tests/test_ollama_service.cpp
    service/OllamaService.cpp
)

target_include_directories(test_ollama_service PRIVATE service)
target_link_libraries(test_ollama_service PRIVATE Catch2::Catch2WithMain jsoncpp_lib)
