cmake_minimum_required(VERSION 4.4.3)
project(red_hot_zombies LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

find_package(glm 1.0.3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(thirdparty/glfw)

add_library(glad STATIC thirdparty/glad/src/gl.c)
target_include_directories(glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include")

add_executable("${CMAKE_PROJECT_NAME}")

# This is useful to get an ASSETS_PATH in your IDE during development
# but you should comment this if you compile a release version and uncomment the next line
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
# Uncomment this line to setup the ASSETS_PATH macro to the final assets directory when you share the game
#target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/") 
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC LOGS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/logs/")

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC SHADERS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/shaders/")

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${SRC_FILES})

target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    # "C:/Dev/libs/glfw/glfw-3.5.1.bin.WIN64/include/GLFW"
)

target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE
    glm::glm
    glfw # "C:/Dev/libs/glfw/glfw-3.5.1.bin.WIN64/lib-mingw-w64/libglfw3.a"
    glad
    OpenGL::GL
)