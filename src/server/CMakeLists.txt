cmake_minimum_required(VERSION 2.8)

project(kp2_server)

set(SRC
	./connection.cpp
	./connectionmanager.cpp
	./main.cpp
	../json/json_reader.cpp
	../json/json_value.cpp
	../json/json_writer.cpp
	../debug/assert.cpp
	../debug/crashcatcher.cpp
	../debug/crashmessage.cpp
	../debug/stack.cpp
	../debug/stacktrace.cpp
	../net/clientsocket.cpp
	../net/packet.cpp
	../net/serversocket.cpp
	../net/socket.cpp
	../net/socketactivity.cpp
	../net/socketset.cpp
	../utils/commandlineparser.cpp
	../utils/outputredirector.cpp
	../utils/inifile.cpp
	../utils/demangle.cpp
	../utils/directory.cpp
	../utils/timer.cpp
	../utils/curve.cpp
	../utils/string.cpp
	../exception/exception.cpp
)

include(../game.cmake)
include(../common.cmake)

IF(WIN32)
	target_link_libraries(kp2_server ws2_32 bfd iberty psapi imagehlp intl)
ENDIF(WIN32)

IF(UNIX)
	target_link_libraries(kp2_server rt dl)	
ENDIF(UNIX)

