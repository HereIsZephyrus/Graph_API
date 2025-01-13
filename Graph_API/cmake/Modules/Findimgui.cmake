find_path(
    IMGUI_INCLUDE_DIR
    imgui.h imgui_impl_glfw.h imgui_impl_opengl3.h
    PATHS
    ${PROJECT_SOURCE_DIR}/../ImGUIopengl3
)

if(IMGUI_INCLUDE_DIR)
    set(IMGUI_FOUND TRUE)
    message(STATUS "Found imgui: ${IMGUI_INCLUDE_DIR}")
else()
    set(IMGUI_FOUND FALSE)
    message(WARNING "imgui not found")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(imgui DEFAULT_MSG IMGUI_FOUND)

if(IMGUI_FOUND)
    set(IMGUI_INCLUDE_DIRS ${IMGUI_INCLUDE_DIR})
    mark_as_advanced(IMGUI_INCLUDE_DIR)
    target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${IMGUI_INCLUDE_DIRS})
endif()

set(IMGUI_INCLUDE_DIRS ${IMGUI_INCLUDE_DIRS} CACHE STRING "The include directory for imgui")
