message("linking glm")
if (NOT glm_FOUND)
    message(STATUS "GLM not found, downloading...")
    FetchContent_Declare(
                         glm_repo
        GIT_REPOSITORY https://github.com/icaven/glm.git
        GIT_TAG master
    )
    message(STATUS "Finish download.")
    FetchContent_MakeAvailable(glm_repo)
endif()
