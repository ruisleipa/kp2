cmake_minimum_required(VERSION 2.8)

project(kp2_editor)

set(UI
	ui/crankshaftform.ui
	ui/mainwindow.ui
	ui/cylinderheadform.ui
	ui/cylinderblockform.ui
	ui/chassisform.ui
	ui/vehicleform.ui
	ui/editform.ui
)

set(SRC
	main.cpp
	mainwindow.cpp
	crankshaftform.cpp
	cylinderheadform.cpp
	cylinderblockform.cpp
	vehicleform.cpp
	chassisform.cpp
	editform.cpp
	objectfactory.cpp
	typespecificformfactory.cpp
	typespecificform.cpp
	../utils/directory.cpp
)

find_package(Qt4 REQUIRED)

include(${QT_USE_FILE})

qt4_wrap_ui(${UI})

set(CMAKE_AUTOMOC TRUE)

add_executable(${PROJECT_NAME} ${SRC} ${UI})

target_link_libraries(${PROJECT_NAME} kp2_physics)
target_link_libraries(${PROJECT_NAME} kp2_game)
target_link_libraries(${PROJECT_NAME} jsoncpp)
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})


