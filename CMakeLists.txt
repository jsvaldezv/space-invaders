# ======================================== Global Configuration ======================================= #
cmake_minimum_required(VERSION 3.5)

# See general configuration values
message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "Project Version: ${PROJECT_VERSION}")

# ======================================= Project Configuration ======================================= #
project(${PROJECT_NAME}
        VERSION ${PROJECT_VERSION}
        DESCRIPTION "C++ Space Invaders Game"
        LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

# Make C++ a hard requirement
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_XCODE_GENERATE_SCHEME OFF)
set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Support macOS down to High Sierra" FORCE)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;PreRelease" CACHE STRING "Configurations" FORCE)

# Add all source files
file(GLOB_RECURSE SOURCE_FILES Source/*.cpp Source/*.h)

# Add executables
add_executable(${PROJECT_NAME} Source/Main.cpp ${SOURCE_FILES})

# C++ Version
target_compile_features(${PROJECT_NAME} PRIVATE ${CPP_VERSION})

# Find Raylib
add_subdirectory(Libraries/raylib)
target_link_libraries(${PROJECT_NAME} raylib)

# Add files to compile 
target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "")

# Set source structure folder
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "" FILES ${SOURCE_FILES})

# Add pre release debug flag
target_compile_definitions(${PROJECT_NAME} PUBLIC $<$<CONFIG:PreRelease>:PRE_RELEASE=1>)

# ========================================= Libraries =========================================== #
# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

# ========================================= IDE env variables ========================================== #
set(CMAKE_XCODE_SCHEME_ENVIRONMENT OS_ACTIVITY_MODE=disable)

# ============================================= Warnings =============================================== #
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
   add_compile_options(-fdiagnostics-color=always)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
   add_compile_options(-fcolor-diagnostics)
endif()