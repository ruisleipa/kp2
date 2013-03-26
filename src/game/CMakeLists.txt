cmake_minimum_required(VERSION 2.8)

project(kp2_game)

set(SRC
	chassis.cpp
	crankshaft.cpp
	cylinderblock.cpp
	cylinderhead.cpp
	object.cpp
	objectfactory.cpp
	objectidmapper.cpp
	part.cpp
	partcontainer.cpp
	player.cpp
	serializable.cpp
	state.cpp
	transmission.cpp
	vehicle.cpp
)

add_library(${PROJECT_NAME} ${SRC})
