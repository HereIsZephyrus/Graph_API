## basic setting
cmake_minimum_required(VERSION 3.25) # for fully support C++17 and multi-platform-configuration
message(STATUS "CMake version: ${CMAKE_VERSION}")
set(CMAKE_CXX_EXTENSIONS OFF)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
include(FetchContent) # not neccessary
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

## create executable
project(
    RouteSystemApplication
    VERSION 1.0
    LANGUAGES CXX C) # glew use C compiler

## add dependencies
add_subdirectory(${PROJECT_SOURCE_DIR}/glew/build/cmake)
add_subdirectory(${PROJECT_SOURCE_DIR}/glm)
add_subdirectory(${PROJECT_SOURCE_DIR}/glfw)

## compile source files
file(GLOB SOURCE_FILES 
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/../ImGUIopengl3/*.cpp
)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

## add include directories
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")
find_package(imgui REQUIRED)
# find_package(GTest REQUIRED)
# target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE gtest)

## configure file for init resurce path
set(SHADER_PATH "${PROJECT_SOURCE_DIR}/OpenGL/shaders/")
configure_file(${PROJECT_SOURCE_DIR}/cmake/config.h.in ${CMAKE_PROJECT_NAME}/../include/config.h)
## copy shader files
add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME} 
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_SOURCE_DIR}/shaders"
    "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/shaders"
)

## set cpp properties
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)
#include(CheckIPOSupported)
#check_ipo_supported(RESULT result)
#if(result)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION FALSE) # glew don't support IPO
#endif()

## link libraries
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/ADT
    ${PROJECT_SOURCE_DIR}/include/OpenGL
    ${PROJECT_SOURCE_DIR}/glfw/include
    ${PROJECT_SOURCE_DIR}/glew/include
    ${PROJECT_SOURCE_DIR}/glm
	${PROJECT_SOURCE_DIR}/../glm
)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glew)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glm::glm)