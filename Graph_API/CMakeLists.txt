cmake_minimum_required(VERSION 3.25)

message(STATUS "CMake version: ${CMAKE_VERSION}")
project(
    RouteSystem
    VERSION 1.0
    LANGUAGES CXX C) # glew use C compiler

add_subdirectory(${PROJECT_SOURCE_DIR}/glew/build/cmake)
add_subdirectory(${PROJECT_SOURCE_DIR}/glm)
add_subdirectory(${PROJECT_SOURCE_DIR}/glfw)
file(GLOB SOURCE_FILES 
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/../ImGUIopengl3/*.cpp
    ${PROJECT_SOURCE_DIR}/glew/src/glew.c
)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

set(CMAKE_CXX_EXTENSIONS OFF)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
include(FetchContent)
find_package(Boost REQUIRED)


set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")
if (APPLE)
    set(glew_platform_libs "-framework AGL" "-framework OpenGL")
elseif (WIN32)
    set(glew_lib glew32)
    set(glew_platform_libs opengl32 glu32)
else()
    find_package(OpenGL REQUIRED)
    set(glew_platform_libs ${OPENGL_LIBRARIES})
endif()
find_package(glfw3 REQUIRED)
find_package(imgui REQUIRED)
# find_package(GTest REQUIRED)
# target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE gtest)

set(SHADER_PATH "${PROJECT_SOURCE_DIR}/OpenGL/shaders/")
configure_file(${PROJECT_SOURCE_DIR}/cmake/config.h.in ${CMAKE_PROJECT_NAME}/include/config.h)

include(CheckIPOSupported)
check_ipo_supported(RESULT result)
if(result)
  set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION FALSE) # glew don't support IPO
endif()
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/ADT
    ${PROJECT_SOURCE_DIR}/include/OpenGL
)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME} 
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_SOURCE_DIR}/shaders"
    "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/shaders"
)