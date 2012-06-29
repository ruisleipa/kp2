cmake_minimum_required(VERSION 2.8)

project(kp2_phystest)

set(SRC
	../physics/clutch.cpp
	../physics/axle.cpp
	../physics/engine.cpp
	../physics/starter.cpp
	../physics/flywheel.cpp
	../physics/transmission.cpp
	../utils/curve.cpp
	../utils/noncopyable.cpp
	./main.cpp
	../json/json_reader.cpp
	../json/json_value.cpp
	../json/json_writer.cpp
)

include(../game.cmake)
include(../common.cmake)
