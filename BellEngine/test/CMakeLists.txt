cmake_minimum_required(VERSION 3.19.3)

set(This BellTests)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS 
    "src/*.cpp"
)

add_executable(${This} ${SOURCES})
#   Link libraries that we are dependant on
target_link_libraries(${This} PUBLIC
    gtest_main
    Bell
)

add_test(
    NAME ${This}
    COMMAND ${This}
)