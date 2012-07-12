cmake_minimum_required(VERSION 2.8)

IF(WIN32)
	add_definitions( -DWINVER=0x0501 )
	add_definitions( -mwindows )
ENDIF(WIN32)

if(MINGW)
  set(CMAKE_RC_COMPILER_INIT windres)
  ENABLE_LANGUAGE(RC)
  SET(CMAKE_RC_COMPILE_OBJECT
    "<CMAKE_RC_COMPILER> -i <SOURCE> -o <OBJECT>")
endif(MINGW)

include_directories(src)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

add_definitions( -std=gnu++0x -Wall -Wextra -g -O0 )

add_subdirectory(src/json)
add_subdirectory(src/physics)
add_subdirectory(src/game)
add_subdirectory(src/editor)
add_subdirectory(src/client)
add_subdirectory(src/server)
add_subdirectory(src/phystest)
