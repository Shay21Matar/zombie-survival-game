cmake_minimum_required(VERSION 3.14)
project(GameTests)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# For MSVC, enable proper C++17 support
if(MSVC)
    add_compile_options(/Zc:__cplusplus)
endif()

# Set Qt path
set(CMAKE_PREFIX_PATH "C:/Qt/6.10.1/mingw_64")

# Find Qt packages
find_package(Qt6 REQUIRED COMPONENTS Core)

# Download and configure GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../code
)

# Add source files from core
set(CORE_SOURCES
    ../code/core/Player.cpp
    ../code/core/scoreboard.cpp
)

# Create test executable
add_executable(
    game_tests
    PlayerTest.cpp
    ScoreBoardTest.cpp
    ${CORE_SOURCES}
)

# Link against GoogleTest, GoogleMock and Qt
target_link_libraries(
    game_tests
    GTest::gtest_main
    GTest::gmock_main
    Qt6::Core
)
