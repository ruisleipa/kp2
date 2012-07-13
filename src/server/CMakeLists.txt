cmake_minimum_required(VERSION 2.8)

project(kp2_server)

set(SRC
	connection.cpp
	connectionmanager.cpp
	main.cpp
	../net/clientsocket.cpp
	../net/packet.cpp
	../net/serversocket.cpp
	../net/socket.cpp
	../net/socketactivity.cpp
	../net/socketset.cpp
	../utils/commandlineparser.cpp
	../utils/outputredirector.cpp
	../utils/demangle.cpp
	../utils/directory.cpp
	../utils/timer.cpp
	../utils/curve.cpp
	../utils/string.cpp
	../exception/exception.cpp
)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} kp2_game)
target_link_libraries(${PROJECT_NAME} jsoncpp)

IF(WIN32)
	target_link_libraries(${PROJECT_NAME} ws2_32 bfd iberty psapi imagehlp intl)
ENDIF(WIN32)

IF(UNIX)
	target_link_libraries(${PROJECT_NAME} rt dl)
ENDIF(UNIX)

