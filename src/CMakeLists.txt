cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

project(converter)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# rapidjson dependency is resolved through conan, see build script :
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(SOURCES
    osm_parser.cpp
    json_dump.cpp
    main.cpp
)

add_executable(converter "${SOURCES}")

set(LIBOSMIUM_LINK_DEPS bz2 z expat -pthread)
target_link_libraries(converter PRIVATE "${LIBOSMIUM_LINK_DEPS}")
