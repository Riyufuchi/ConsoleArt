cmake_minimum_required(VERSION 3.20)
project(ConsoleArt LANGUAGES C CXX)

#
# C++ Standard
#
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#
# Warnings
#
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	add_compile_options(-Wall -Wextra -pedantic)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	add_compile_options(/W4)
endif()

#
# Other settings
#
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	add_compile_definitions(NOMINMAX)
endif()

#
# Optimization
#
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
	set(CMAKE_C_FLAGS_RELEASE "-O3")
	#
	set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -DDEBUG")
	set(CMAKE_C_FLAGS_DEBUG "-O0 -g -DDEBUG")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set(CMAKE_CXX_FLAGS_RELEASE "/O2")
	set(CMAKE_C_FLAGS_RELEASE "/O2")
	#
	set(CMAKE_CXX_FLAGS_DEBUG "/Od /Zi /DDEBUG")
	set(CMAKE_C_FLAGS_DEBUG "/Od /Zi /DDEBUG")
endif()

#
# PREBUILT STATIC LIBRARIES
#
set(GENERAL_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

set(CONSOLE_LIB_DIR ${GENERAL_LIB_DIR}/ConsoleLib)
set(COMPONENT-SDL_LIB_DIR ${GENERAL_LIB_DIR}/ComponentSDL)

# Create an IMPORTED target for the .a file
add_library(ConsoleLib STATIC IMPORTED)
add_library(ComponentSDL STATIC IMPORTED)

# Point the IMPORTED target to the actual file
if (WIN32)
	set_target_properties(ConsoleLib PROPERTIES
	IMPORTED_LOCATION ${CONSOLE_LIB_DIR}/ConsoleLib.lib
	INTERFACE_INCLUDE_DIRECTORIES ${CONSOLE_LIB_DIR}/inc)
	
	set_target_properties(ComponentSDL PROPERTIES
	IMPORTED_LOCATION ${COMPONENT-SDL_LIB_DIR}/ComponentSDL.lib
	INTERFACE_INCLUDE_DIRECTORIES ${COMPONENT-SDL_LIB_DIR}/inc)
else()
	set_target_properties(ConsoleLib PROPERTIES
	IMPORTED_LOCATION ${CONSOLE_LIB_DIR}/libConsoleLib.a
	INTERFACE_INCLUDE_DIRECTORIES ${CONSOLE_LIB_DIR}/inc)
	
	set_target_properties(ComponentSDL PROPERTIES IMPORTED_LOCATION
	${COMPONENT-SDL_LIB_DIR}/libComponentSDL.a
	INTERFACE_INCLUDE_DIRECTORIES ${COMPONENT-SDL_LIB_DIR}/inc)
endif()

#
# SDL2 set up
#
set(SDL_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL)

add_library(SDL2 STATIC IMPORTED)

if (WIN32)
	add_library(SDL2_main STATIC IMPORTED)

	set_target_properties(SDL2 PROPERTIES
	IMPORTED_LOCATION ${SDL_LIB_DIR}/windows/x64/SDL2.lib
	INTERFACE_INCLUDE_DIRECTORIES ${SDL_LIB_DIR})

	set_target_properties(SDL2_main PROPERTIES
	IMPORTED_LOCATION ${SDL_LIB_DIR}/windows/x64/SDL2main.lib
	INTERFACE_INCLUDE_DIRECTORIES ${SDL_LIB_DIR})
else()
	set_target_properties(SDL2 PROPERTIES
	IMPORTED_LOCATION ${SDL_LIB_DIR}/linux/libSDL2.a
	INTERFACE_INCLUDE_DIRECTORIES ${SDL_LIB_DIR})
endif()

#
# Application
#
file(MAKE_DIRECTORY build)

file(GLOB_RECURSE APP_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(ConsoleArt ${APP_SOURCES})

if (WIN32)
	set_target_properties(ConsoleArt PROPERTIES WIN32_EXECUTABLE OFF)
endif()


# Link everything
target_include_directories(ConsoleArt PRIVATE
	${CONSOLE_LIB_DIR}/inc
	${COMPONENT-SDL_LIB_DIR}/inc
	${SDL_LIB_DIR}
)

if (WIN32)
	target_link_libraries(ConsoleArt PRIVATE
	ConsoleLib
	ComponentSDL
	SDL2
	SDL2_main
)
else()
	target_link_libraries(ConsoleArt PRIVATE
	ConsoleLib
	ComponentSDL
	SDL2
)
endif()

# Copy assets folder into build directory
if (WIN32)
	file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION "${CMAKE_BINARY_DIR}/Release")
	file(COPY ${CMAKE_SOURCE_DIR}/libs/SDL/windows/x64/SDL2.dll DESTINATION "${CMAKE_BINARY_DIR}/Release")
else()
	file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
endif()

#
# Documentation
#

# Path to LaTeX source folder
set(LATEX_DIR ${CMAKE_CURRENT_SOURCE_DIR}/latex-doc)
set(MAIN_TEX ConsoleArt.tex)
set(OUTPUT_PDF ${CMAKE_CURRENT_BINARY_DIR}/ConsoleArt.pdf)

# Custom target to build docs
add_custom_target(docs
	COMMAND ${CMAKE_COMMAND} -E chdir ${LATEX_DIR} lualatex ${MAIN_TEX}
	COMMAND ${CMAKE_COMMAND} -E chdir ${LATEX_DIR} makeglossaries ConsoleArt
	COMMAND ${CMAKE_COMMAND} -E chdir ${LATEX_DIR} lualatex ${MAIN_TEX}
	COMMAND ${CMAKE_COMMAND} -E chdir ${LATEX_DIR} lualatex ${MAIN_TEX}
	COMMENT "Building PDF documentation with lualatex and makeglossaries"
)

