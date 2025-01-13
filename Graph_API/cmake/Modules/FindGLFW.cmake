set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};/opt/homebrew/Cellar/glfw/3.4/lib") # channingtong mac PATH
set(GLFW3_INCLUDE_DIRS /opt/homebrew/Cellar/glfw/3.4/include)
set(GLFW3_LIBRARIES /opt/homebrew/Cellar/glfw/3.4/lib)
include_directories(${GLFW3_INCLUDE_DIRS})
link_directories(${GLFW3_LIBRARIES})
find_package(glfw3 REQUIRED)
if (NOT GLFW_FOUND)
    message(STATUS "GLFW not found, downloading...")
    FetchContent_Declare(
        glfw_repo
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG master
    )
    FetchContent_MakeAvailable(glfw_repo)
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glfw)
endif()
