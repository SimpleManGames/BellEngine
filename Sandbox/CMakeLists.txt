# cmake_minimum_required(VERSION 3.19.3)

set(SANDBOX_PROJECT Sandbox)
# Folder name of the location we store the app assets
set(ASSET_FOLDER_NAME assets)

project(${SANDBOX_PROJECT} VERSION 1.0 DESCRIPTION "Sandbox Environment for Developing Bell" LANGUAGES CXX)

set(SANDBOX_SOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/SandboxApp.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Sandbox2D.cpp"
)

set(IMGUI_SOURCE
    "../BellEngine/libs/imgui/imgui.cpp"
    "../BellEngine/libs/imgui/imgui_demo.cpp"
    "../BellEngine/libs/imgui/imgui_draw.cpp"
    "../BellEngine/libs/imgui/imgui_tables.cpp"
    "../BellEngine/libs/imgui/imgui_widgets.cpp"
)

include_directories(include)

add_executable(${SANDBOX_PROJECT} ${SANDBOX_SOURCE} ${IMGUI_SOURCE})

set_target_properties(${SANDBOX_PROJECT} PROPERTIES CXX_STANDARD 17)

target_include_directories(${SANDBOX_PROJECT} PUBLIC include)

target_link_libraries(${SANDBOX_PROJECT} PRIVATE Bell)

# Move the assets folder next to the EXE
add_custom_command(
    TARGET ${SANDBOX_PROJECT} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/${ASSET_FOLDER_NAME}
    $<TARGET_FILE_DIR:${SANDBOX_PROJECT}>/${ASSET_FOLDER_NAME}
)