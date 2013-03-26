cmake_minimum_required(VERSION 2.8)

project(kp2_client)

set(UI
	ui/carlistmenu.ui
	ui/carshopmenu.ui
	ui/gamemainmenu.ui
	ui/gameview.ui
	ui/gameloadingscreen.ui
	ui/garagemenu.ui
	ui/loadingscreen.ui
	ui/mainmenu.ui
	ui/mainwindow.ui
	ui/menucontainer.ui
	ui/multiplayermenu.ui
	ui/scoresmenu.ui
	ui/settingsmenu.ui
	ui/singleplayermenu.ui
)

set(SRC
	application.cpp
	carshopmenu.cpp
	clientobjectfactory.cpp
	connection.cpp
	gamemainmenu.cpp
	gamemenu.cpp
	gameview.cpp
	gameloadingscreen.cpp
	garagemenu.cpp
	main.cpp
	mainmenu.cpp
	mainwindow.cpp
	menucontainer.cpp
	menu.cpp
	objectidmapper.cpp
	playerproxy.cpp
	multiplayermenu.cpp
	settingsmenu.cpp
	singleplayermenu.cpp
	state.cpp
	updater.cpp
	../views/tableview.cpp
	../models/vehicletablemodel.cpp
	../models/abstractobjecttablemodel.cpp
	../net/packet.cpp
	../sounds/musicplayer.cpp
	../utils/curve.cpp
	../utils/demangle.cpp
	../utils/directory.cpp
	../utils/outputredirector.cpp
	../exception/exception.cpp
)

set(QT_USE_QTNETWORK 1)

find_package(Qt4 REQUIRED)

include(${QT_USE_FILE})

qt4_wrap_ui(${UI})

set(CMAKE_AUTOMOC TRUE)

add_executable(${PROJECT_NAME} ${SRC} ${UI})

target_link_libraries(${PROJECT_NAME} audiere)
target_link_libraries(${PROJECT_NAME} kp2_game)
target_link_libraries(${PROJECT_NAME} jsoncpp)
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})

IF(WIN32)
	target_link_libraries(${PROJECT_NAME} ws2_32)
ENDIF(WIN32)


