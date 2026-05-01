set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

cmake_minimum_required(VERSION 4.0)
project(ACGRUX VERSION 1.0.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/generator.cpp
  src/profile.h
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)

find_package(fltk CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)

target_include_directories(${PROJECT_NAME}
  PRIVATE
  ${fltk_INCLUDE_DIRS}
  ${yaml-cpp_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  ${fltk_LIBRARIES}
  ${yaml-cpp_LIBRARIES}
)
