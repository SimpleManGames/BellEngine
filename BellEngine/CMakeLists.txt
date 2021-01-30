file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS 
    "src/*.cpp"
    "libs/stb_image/stb_image.cpp")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS 
    "include/*.h"
    "libs/stb_image/stb_image.h")

#           DEFINITIONS
add_definitions(-DB_DEBUG) # B_DEBUG

add_library(Bell STATIC ${SOURCES} ${HEADERS})

target_precompile_headers(Bell PUBLIC include/bpch.h)

# Using some VS17 features
set_target_properties(Bell PROPERTIES CXX_STANDARD 17)

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

target_include_directories(Bell 
    PUBLIC include
    PUBLIC libs/spdlog/include
    PUBLIC libs/glm
    PUBLIC libs/glfw/include
    PUBLIC libs/imgui/examples
    PUBLIC libs/imgui
    PUBLIC libs/entt/single_include)

target_link_directories(Bell
    PUBLIC libs/spdlog/src
    PUBLIC libs/glfw/src
    PUBLIC libs/imgui/examples
    PUBLIC libs/imgui
    PUBLIC libs/entt/src)

target_link_libraries(Bell 
    PUBLIC spdlog 
    PUBLIC glm 
    PUBLIC glfw
    PUBLIC glad
    PUBLIC EnTT)
