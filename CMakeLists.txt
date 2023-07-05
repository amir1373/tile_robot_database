cmake_minimum_required(VERSION 3.22)
project(tile_robot_database)

add_subdirectory(libpqxx)

set(PostgreSQL_INCLUDE_DIRS build/libpqxx/include)

include_directories(
  ${CMAKE_SOURCE_DIR}/include
  ${PostgreSQL_INCLUDE_DIRS}
)

add_library( ${PROJECT_NAME}
    src/DatabaseManager.cpp
)

add_executable(main src/main.cpp)
target_link_libraries(main ${PROJECT_NAME} pqxx)