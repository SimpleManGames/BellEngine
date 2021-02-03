# cmake_minimum_required(VERSION 3.19.3)

set(EDITOR_PROJECT_NAME BellEditor)

project(${EDITOR_PROJECT_NAME} VERSION 1.0 DESCRIPTION "Editting Environment for creating applications with Bell" LANGUAGES CXX)

set(EDITOR_SOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/BellEditorApp.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/EditorLayer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Panels/SceneHierarchyPanel.cpp"
)

set(IMGUI_SOURCE
    "../BellEngine/libs/imgui/imgui.cpp"
    "../BellEngine/libs/imgui/imgui_demo.cpp"
    "../BellEngine/libs/imgui/imgui_draw.cpp"
    "../BellEngine/libs/imgui/imgui_tables.cpp"
    "../BellEngine/libs/imgui/imgui_widgets.cpp"
)

add_executable(${EDITOR_PROJECT_NAME} ${EDITOR_SOURCE} ${IMGUI_SOURCE})

set_target_properties(${EDITOR_PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

target_include_directories(
    ${EDITOR_PROJECT_NAME} 
    PUBLIC include
    PUBLIC include/Panels)

target_link_libraries(
    ${EDITOR_PROJECT_NAME}
    PRIVATE Bell)

# Move the assets folder next to the EXE
add_custom_command(
    TARGET ${EDITOR_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/${ASSET_FOLDER_NAME}
    $<TARGET_FILE_DIR:${EDITOR_PROJECT_NAME}>/${ASSET_FOLDER_NAME}
)