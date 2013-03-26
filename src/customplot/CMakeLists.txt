cmake_minimum_required(VERSION 2.8)

project(customplot)

set(SRC
	qcustomplot.cpp
)

find_package(Qt4 REQUIRED)

include(${QT_USE_FILE})

set(CMAKE_AUTOMOC TRUE)

add_library(${PROJECT_NAME} ${SRC})
