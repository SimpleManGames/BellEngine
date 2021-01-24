# cmake_minimum_required(VERSION 3.19.3)

project(Sandbox VERSION 1.0 DESCRIPTION "Sandbox Environment for Developing Bell" LANGUAGES CXX)

# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../BellEngine ${CMAKE_CURRENT_BINARY_DIR}/BellEngine)

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

add_executable(Sandbox ${SANDBOX_SOURCE} ${IMGUI_SOURCE})

set_target_properties(Sandbox PROPERTIES CXX_STANDARD 17)

target_include_directories(Sandbox 
    PUBLIC include)

target_link_libraries(Sandbox PRIVATE Bell)