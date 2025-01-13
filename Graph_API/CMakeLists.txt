cmake_minimum_required(VERSION 3.25)

message(STATUS "CMake version: ${CMAKE_VERSION}")
project(
    RouteSystem
    VERSION 1.0
    LANGUAGES CXX)

file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

set(CMAKE_CXX_EXTENSIONS OFF)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
include(FetchContent)
find_package(Boost REQUIRED)


set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")
find_package(imgui REQUIRED)
find_package(glfw3 REQUIRED)
#find_package(glew REQUIRED)
find_package(glm REQUIRED)
# find_package(GTest REQUIRED)

set(SHADER_PATH "${PROJECT_SOURCE_DIR}/OpenGL/shaders/")
configure_file(${PROJECT_SOURCE_DIR}/cmake/config.h.in ${CMAKE_PROJECT_NAME}/include/config.h)

include(CheckIPOSupported)
check_ipo_supported(RESULT result)
if(result)
  set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
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

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glfw)
#target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glew)
add_subdirectory(${PROJECT_SOURCE_DIR}/glew/build/cmake)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glm::glm)
# target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE gtest)

add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME} 
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_SOURCE_DIR}/shaders"
    "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/shaders"
)