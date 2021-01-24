# cmake_minimum_required(VERSION 3.19.3)

set(EDITOR_PROJECT_NAME BellEditor)

project(${EDITOR_PROJECT_NAME} VERSION 1.0 DESCRIPTION "Editting Environment for creating applications with Bell" LANGUAGES CXX)

# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../BellEngine ${CMAKE_CURRENT_BINARY_DIR}/BellEngine)

set(EDITOR_SOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/BellEditorApp.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/EditorLayer.cpp"
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
    PUBLIC include)

target_link_libraries(
    ${EDITOR_PROJECT_NAME}
    PRIVATE Bell)