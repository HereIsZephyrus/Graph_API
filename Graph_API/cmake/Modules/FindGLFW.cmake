message("linking glfw")
if (NOT glfw3_FOUND)
    message(STATUS "GLFW not found, downloading...")
    FetchContent_Declare(
        glfw_repo
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG master
    )
    FetchContent_MakeAvailable(glfw_repo)
endif()
