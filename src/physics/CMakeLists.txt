cmake_minimum_required(VERSION 2.8)

project(kp2_physics)

set(SRC
	axle.cpp
	clutch.cpp
	engine.cpp
	flywheel.cpp
	process.cpp
	starter.cpp
	transmission.cpp
	vehicle.cpp
)

add_library(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} jsoncpp)
target_link_libraries(${PROJECT_NAME} kp2_game)
