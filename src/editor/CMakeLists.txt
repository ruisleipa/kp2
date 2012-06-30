cmake_minimum_required(VERSION 2.8)

project(kp2_editor)

set(UI
	./ui/crankshaftform.ui
	./ui/mainwindow.ui
	./ui/cylinderheadform.ui
	./ui/cylinderblockform.ui
	./ui/chassisform.ui
	./ui/vehicleform.ui
	./ui/editform.ui
)

set(SRC
	./main.cpp
	./mainwindow.cpp
	./crankshaftform.cpp
	./cylinderheadform.cpp
	./cylinderblockform.cpp
	./vehicleform.cpp
	./chassisform.cpp
	./editform.cpp
	./typespecificformfactory.cpp
	./typespecificform.cpp
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

