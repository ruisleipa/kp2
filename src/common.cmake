add_definitions( -std=gnu++0x -Wall -Wextra -g -O0 )

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

include_directories(../)
include_directories(./)
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

add_executable(${PROJECT_NAME} ${SRC} ${UI})

target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})
