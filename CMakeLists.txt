cmake_minimum_required(VERSION 2.8)

project(kp2)

add_definitions( -std=gnu++0x -Wall -Wextra -g )

IF(WIN32)
	add_definitions( -DWINVER=0x0501 )	
ENDIF(WIN32)

add_subdirectory(src/client)
add_subdirectory(src/server)
add_subdirectory(src/phystest)
