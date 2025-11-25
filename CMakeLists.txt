cmake_minimum_required(VERSION 3.20)
project(MyApp LANGUAGES C CXX)

# --- C++ Standard ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Default build type ---
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

# --- Warnings ---
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -pedantic)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4)
endif()

# --- Optimization ---
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# ---------------------------------------------------------
#              PREBUILT STATIC LIBRARIES (.a)
# ---------------------------------------------------------

set(CONSOLE_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/ConsoleLib)
set(COMPONENT-SDL_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/ComponentSDL)

# Create an IMPORTED target for the .a file
add_library(ConsoleLib STATIC IMPORTED)
add_library(ComponentSDL STATIC IMPORTED)

# Point the IMPORTED target to the actual file
set_target_properties(ConsoleLib PROPERTIES IMPORTED_LOCATION ${CONSOLE_LIB_DIR}/libConsoleLib.a INTERFACE_INCLUDE_DIRECTORIES ${CONSOLE_LIB_DIR}/inc)
set_target_properties(ComponentSDL PROPERTIES IMPORTED_LOCATION ${COMPONENT-SDL_LIB_DIR}/libComponentSDL.a INTERFACE_INCLUDE_DIRECTORIES ${COMPONENT-SDL_LIB_DIR}/inc)

# ---------------------------------------------------------
#                       SDL2
# ---------------------------------------------------------
if (WIN32)
    #
    # Windows: require SDL2_DIR, SDL2_image_DIR, SDL2_ttf_DIR
    # (User must download SDL dev folders and point CMake to them)
    #
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)

else()
    #
    # Linux / macOS: prefer pkg-config
    #
    find_package(PkgConfig REQUIRED)

    pkg_check_modules(SDL2 IMPORTED_TARGET sdl2)
    pkg_check_modules(SDL2_IMAGE IMPORTED_TARGET SDL2_image)
    pkg_check_modules(SDL2_TTF IMPORTED_TARGET SDL2_ttf)

    # For compatibility the library names should be consistent
    add_library(SDL2::SDL2 INTERFACE IMPORTED)
    target_link_libraries(SDL2::SDL2 INTERFACE PkgConfig::SDL2)

    add_library(SDL2_image::SDL2_image INTERFACE IMPORTED)
    target_link_libraries(SDL2_image::SDL2_image INTERFACE PkgConfig::SDL2_IMAGE)

    add_library(SDL2_ttf::SDL2_ttf INTERFACE IMPORTED)
    target_link_libraries(SDL2_ttf::SDL2_ttf INTERFACE PkgConfig::SDL2_TTF)

endif()

# ---------------------------------------------------------
#                       APP
# ---------------------------------------------------------
file(GLOB_RECURSE APP_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(ConsoleArt ${APP_SOURCES})

# Link everything
target_include_directories(ConsoleArt PRIVATE
    ${CONSOLE_LIB_DIR}/inc
    ${COMPONENT-SDL_LIB_DIR}/inc
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
)

target_link_libraries(ConsoleArt PRIVATE
    ConsoleLib
    ComponentSDL
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
)

# Copy assets folder into build directory
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

