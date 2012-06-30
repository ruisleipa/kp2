cmake_minimum_required(VERSION 2.8)

project(kp2_editor)

set(UI
	./ui/mainwindow.ui
)

set(SRC
	./main.cpp
	./mainwindow.cpp
	../json/json_reader.cpp
	../json/json_value.cpp
	../json/json_writer.cpp
	../utils/curve.cpp
	../views/tableview.cpp
	../models/vehicletablemodel.cpp
	../models/abstractobjecttablemodel.cpp
)

include(../game.cmake)
include(../qt.cmake)
include(../common.cmake)

