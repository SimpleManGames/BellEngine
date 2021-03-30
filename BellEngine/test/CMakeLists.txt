cmake_minimum_required(VERSION 3.19.3)

set(This BellTests)

set(SOURCES
    "src/BellTests.cpp"
    "src/LayerStackTests.cpp"
    "src/TestLayer.h"
)

set(IMGUI_SOURCE
    "../libs/imgui/imgui.cpp"
    "../libs/imgui/imgui_demo.cpp"
    "../libs/imgui/imgui_draw.cpp"
    "../libs/imgui/imgui_tables.cpp"
    "../libs/imgui/imgui_widgets.cpp"
)

add_executable(${This} ${SOURCES} ${IMGUI_SOURCE})

#   Link libraries that we are dependant on
target_link_libraries(${This} PUBLIC
    gtest_main
    Bell
)

add_test(
    NAME ${This}
    COMMAND ${This}
)

# Move the assets folder next to the EXE
add_custom_command(
    TARGET ${This} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/${ASSET_FOLDER_NAME}
    $<TARGET_FILE_DIR:${This}>/${ASSET_FOLDER_NAME}
)