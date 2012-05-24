set(simulation_SRCS
	../physics/clutch.cpp
	../physics/axle.cpp
	../physics/engine.cpp
	../physics/starter.cpp
	../physics/flywheel.cpp
	../physics/transmission.cpp
	../utils/curve.cpp
	../utils/noncopyable.cpp
	../game/serializable.cpp
)

set(game_SRCS
	../game/camshaft.cpp
	../game/charger.cpp
	../game/chassis.cpp
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
	../game/partcontainer.cpp
	../game/player.cpp
	../game/serializable.cpp
	../game/state.cpp
	../game/tire.cpp
	../game/transmission.cpp
	../game/upgrade.cpp
	../game/vehicle.cpp
)


set(phystest_SRCS
	./main.cpp
	../json/json_reader.cpp
	../json/json_value.cpp
	../json/json_writer.cpp
)

include_directories(../)
include_directories(./)
include_directories( ${CMAKE_BINARY_DIR} )

add_executable(kp2_phystest  ${phystest_SRCS} ${simulation_SRCS} ${game_SRCS})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/..)

target_link_libraries(kp2_phystest)

IF(WIN32)
	target_link_libraries(kp2_phystest)
ENDIF(WIN32)

IF(UNIX)
	target_link_libraries(kp2_phystest)
ENDIF(UNIX)

