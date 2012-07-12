cmake_minimum_required(VERSION 2.8)

project(kp2_physics)

set(SRC
	clutch.cpp
	axle.cpp
	starter.cpp
	flywheel.cpp
	transmission.cpp
)

add_library(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} jsoncpp)
target_link_libraries(${PROJECT_NAME} kp2_game)
