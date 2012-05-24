set(phystest_SRCS
	./main.cpp
)

include_directories(../)
include_directories(./)
include_directories( ${CMAKE_BINARY_DIR} )

add_executable(kp2_phystest  ${phystest_SRCS})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/..)

target_link_libraries(kp2_phystest)

IF(WIN32)
	target_link_libraries(kp2_phystest)
ENDIF(WIN32)

IF(UNIX)
	target_link_libraries(kp2_phystest)
ENDIF(UNIX)

