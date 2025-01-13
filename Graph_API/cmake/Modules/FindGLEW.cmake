# Tested only on Mac OS X Mavericks with GLEW v1.10.0.FROM https://gist.github.com/christophercrouzet/85f49dfe8b6c02b9ec6e.js
function(build_glew root_dir)
    set(glew_lib GLEW)
    
    if (APPLE)
        set(glew_platform_libs "-framework AGL" "-framework OpenGL")
    elseif (WIN32)
        set(glew_lib glew32)
        set(glew_platform_libs opengl32 glu32)
    else()
        find_package(OpenGL REQUIRED)
        set(glew_platform_libs ${OPENGL_LIBRARIES})
    endif()

    set(glew_include_dir ${root_dir}/../glew)
    set(glew_src_dir ${root_dir}/src)
    
    set(
        glew_h_files
        ${glew_include_dir}/GL/glew.h
        ${glew_include_dir}/GL/glxew.h
        ${glew_include_dir}/GL/wglew.h
    )
    
    set(
        glew_cxx_files
        ${glew_src_dir}/glew.c
    )
    
    set(glew_source_files ${glew_h_files} ${glew_cxx_files})
    
    add_library(${glew_lib} STATIC ${glew_source_files})
    
    set_property(
        TARGET ${glew_lib}
        APPEND
        PROPERTY COMPILE_DEFINITIONS GLEW_NO_GLU GLEW_STATIC
    )
    
    target_include_directories(${glew_lib} PUBLIC ${glew_include_dir})
    
    if (glew_platform_libs)
        target_link_libraries(${glew_lib} ${glew_platform_libs})
    endif()
    
    get_property(glew_lib_filename TARGET ${glew_lib} PROPERTY LOCATION)
    
    set(
        GLEW_INCLUDE_DIRS
        ${glew_include_dir}
        CACHE INTERNAL
        "Include directories for GLEW"
    )
    
    set(
        GLEW_LIBRARIES
        ${glew_lib_filename}
        CACHE INTERNAL
        "Libraries for GLEW"
    )
endfunction()

message("linking glew")
if (NOT glew_FOUND)
    message(STATUS "GLEW not found, downloading...")
    FetchContent_Declare(
        glew_repo
        GIT_REPOSITORY https://github.com/nigels-com/glew.git
        GIT_TAG master
    )
    message(STATUS "Finish download.")
    FetchContent_MakeAvailable(glew_repo)
endif()
# build_glew(${PROJECT_SOURCE_DIR})
