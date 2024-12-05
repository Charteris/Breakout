cmake_minimum_required(VERSION 3.29.3)
project(Breakout VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(PRINT_DEBUG_LOGS)

# add_compile_definitions(USE_LOG_FILES)

# Setup project dependencies
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/glfw)
find_package(OpenGL REQUIRED)

set(HEADERS
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Game.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Logs.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Config.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/ResourceManager.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/util/Shader.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/util/Texture.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/entity/Entity.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/entity/Brick.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/entity/Structures.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/objects/Level.h
)

set(SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/game.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/config.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/resourceManager.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/util/shader.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/util/texture.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/entity/entity.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/entity/brick.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/objects/level.cpp
)

set(EXTERN ${CMAKE_CURRENT_SOURCE_DIR}/src/extern/glad.c)

add_executable(Breakout ${HEADERS} ${SOURCES} ${EXTERN})
target_include_directories(Breakout PRIVATE src include)
target_link_libraries(Breakout glfw OpenGL::GL)

# Setup testing dependencies
enable_testing()
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# set(TESTS ${CMAKE_CURRENT_SOURCE_DIR}/test/mainTest.cpp)

# add_executable(BreakoutTest ${TESTS})
# target_include_directories(Breakout PRIVATE test)
# target_link_libraries(BreakoutTest GTest::gtest_main)

# include(GoogleTest)
# gtest_discover_tests(BreakoutTest)