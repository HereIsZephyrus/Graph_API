cmake_minimum_required(VERSION 3.25)

message(STATUS "CMake version: ${CMAKE_VERSION}")
project(
    RouteSystem
    VERSION 1.0
    LANGUAGES CXX)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    set_property(TARGET TargetName PROPERTY CXX_STANDARD 17)
    set_target_properties(TargetName PROPERTIES CXX_STANDARD 17)
    target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Testing only available if this is the main app
    # Note this needs to be done in the main CMakeLists
    # since it calls enable_testing, which must be in the
    # main CMakeLists.
    include(CTest)

    # Docs only available if this is the main app
    find_package(Doxygen)
    if(Doxygen_FOUND)
    add_subdirectory(docs)
    else()
    message(STATUS "Doxygen not found, not building docs")
    endif()
endif()

include(FetchContent)
find_package(Boost REQUIRED)

include(CheckIPOSupported)
check_ipo_supported(RESULT result)
if(result)
  set_target_properties(foo PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(imfui REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLFW REQUIRED)
find_package(glm REQUIRED)

set(SHADER_PATH "${PROJECT_SOURCE_DIR}/OpenGL/shaders/")
configure_file(config.h.in config.h)

add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE imfui::imfui)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE GLEW::GLEW)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glm)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
   AND BUILD_TESTING)
  add_subdirectory(tests)
endif()

add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME} 
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_SOURCE_DIR}/shaders"
    "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/shaders"
)