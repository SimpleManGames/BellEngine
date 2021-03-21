cmake_minimum_required(VERSION 3.19.3)

set(This BellTests)

set(SOURCES
    "src/BellTests.cpp"
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
    gmock_main
    Bell
)

add_test(
    NAME ${This}
    COMMAND ${This}
)