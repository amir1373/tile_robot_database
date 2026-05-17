cmake_minimum_required(VERSION 3.22)

project(tile_robot_database LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libpqxx)

add_library(${PROJECT_NAME}
  src/DatabaseManager.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/libpqxx/include
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    pqxx
)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE ${PROJECT_NAME})