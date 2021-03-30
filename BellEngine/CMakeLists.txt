file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS 
    "src/*.cpp"
    "libs/stb_image/stb_image.cpp")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS 
    "include/*.h"
    "libs/stb_image/stb_image.h")

set(This Bell)

#           OPTIONS
option(BELL_DEBUG "Sets the B_DEBUG Preprocessor Macro" ON)

add_library(${This} STATIC ${SOURCES} ${HEADERS})

#           DEFINITIONS
if(BELL_DEBUG)
message(STATUS "B_DEBUG=ON")
target_compile_definitions(${This} PUBLIC B_DEBUG=1) # B_DEBUG
else()
message(STATUS "B_DEBUG=OFF")
target_compile_definitions(${This} PUBLIC B_DEBUG=0) # B_DEBUG
endif()

target_precompile_headers(${This} PUBLIC include/bpch.h)

# Using some VS17 features
set_target_properties(${This} PROPERTIES CXX_STANDARD 17)

#           Tell CMake we'll having tests
enable_testing()

#           DOWNLOAD ALL THE SUBMODULES
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}../.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

#           CHECK ALL THE SUBMODULES
#   spdlog
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libs/spdlog/CMakeLists.txt")
    message(FATAL_ERROR "The spdlog submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

add_subdirectory(libs/spdlog)

#   glm
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libs/glm/CMakeLists.txt")
    message(FATAL_ERROR "The glm submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

add_subdirectory(libs/glm)

#   glfw
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The glfw submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_INSTALL OFF)

add_subdirectory(libs/glfw)

#   imgui does not have a CMakeLists by default, so add the files directly
include_directories("libs/imgui")

include_directories("libs/stb_image")

#   glad
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libs/glad/CMakeLists.txt")
    message(FATAL_ERROR "The glad submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

add_subdirectory(libs/glad)

#   EnTT
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libs/entt/CMakeLists.txt")
    message(FATAL_ERROR "The EnTT submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

add_subdirectory(libs/entt)

#   yaml-cpp
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libs/yaml-cpp/CMakeLists.txt")
    message(FATAL_ERROR "The yaml-cpp submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

add_subdirectory(libs/yaml-cpp)

#   googletest
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libs/googletest/CMakeLists.txt")
    message(FATAL_ERROR "The googletest submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

#   We want to use gMock in our tests
set(BUILD_GMOCK false)

add_subdirectory(libs/googletest)

add_subdirectory(test)

target_include_directories(${This} 
    PUBLIC include
    PUBLIC libs/spdlog/include
    PUBLIC libs/glm
    PUBLIC libs/glfw/include
    PUBLIC libs/imgui/examples
    PUBLIC libs/imgui
    PUBLIC libs/entt/single_include
    PUBLIC libs/yaml-cpp/include
    PUBLIC libs/include(GoogleTest))

target_link_directories(${This}
    PUBLIC libs/spdlog/src
    PUBLIC libs/glfw/src
    PUBLIC libs/imgui/examples
    PUBLIC libs/imgui
    PUBLIC libs/entt/src
    PUBLIC libs/yaml-cpp/src)

target_link_libraries(${This} 
    PUBLIC spdlog 
    PUBLIC glm 
    PUBLIC glfw
    PUBLIC glad
    PUBLIC EnTT
    PUBLIC yaml-cpp)