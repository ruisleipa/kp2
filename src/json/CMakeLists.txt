cmake_minimum_required(VERSION 2.8)

project(jsoncpp)

set(SRC
	json_reader.cpp
	json_value.cpp
	json_writer.cpp
)

add_library(${PROJECT_NAME} ${SRC})
