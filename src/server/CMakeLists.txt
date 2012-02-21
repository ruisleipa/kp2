set(game_SRCS
	../game/camshaft.cpp
	../game/charger.cpp
	../game/clutch.cpp
	../game/cooler.cpp
	../game/cylinderhead.cpp
	../game/differential.cpp
	../game/engine.cpp
	../game/exhaustmanifold.cpp
	../game/exhaustpipe.cpp
	../game/fuelintake.cpp
	../game/fuelpump.cpp
	../game/injector.cpp
	../game/intakemanifold.cpp
	../game/object.cpp
	../game/objectfactory.cpp
	../game/part.cpp
	../game/player.cpp
	../game/state.cpp
	../game/stateactionlistener.cpp
	../game/tire.cpp
	../game/transmission.cpp
	../game/upgrade.cpp
	../game/vehicle.cpp
)

set(server_SRCS
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

include_directories(../)
include_directories(./)
include_directories( ${CMAKE_BINARY_DIR} )

add_definitions( -DKP2_SERVER )

add_executable(kp2_server  ${server_SRCS} ${game_SRCS} )

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/..)

target_link_libraries(kp2_server)

IF(WIN32)
	target_link_libraries(kp2_server ws2_32 bfd iberty psapi imagehlp intl)
ENDIF(WIN32)

IF(UNIX)
	target_link_libraries(kp2_server rt dl)	
ENDIF(UNIX)

