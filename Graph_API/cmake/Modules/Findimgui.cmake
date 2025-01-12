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

# 如果找到，设置 IMGUI_INCLUDE_DIRS 变量
if(IMGUI_FOUND)
    set(IMGUI_INCLUDE_DIRS ${IMGUI_INCLUDE_DIR})
    mark_as_advanced(IMGUI_INCLUDE_DIR)
endif()

# 导出结果
set(IMGUI_INCLUDE_DIRS ${IMGUI_INCLUDE_DIRS} CACHE STRING "The include directory for imgui")
