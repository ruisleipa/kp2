cmake_minimum_required(VERSION 2.8)

project(kp2_client)

set(UI
	./ui/carlistmenu.ui
	./ui/carshopmenu.ui
	./ui/gamemainmenu.ui
	./ui/gameview.ui
	./ui/gameloadingscreen.ui
	./ui/garagemenu.ui
	./ui/loadingscreen.ui
	./ui/mainmenu.ui
	./ui/mainwindow.ui
	./ui/menucontainer.ui
	./ui/multiplayermenu.ui
	./ui/scoresmenu.ui
	./ui/settingsmenu.ui
	./ui/singleplayermenu.ui
)

set(SRC
	./carshopmenu.cpp
	./clientobjectfactory.cpp
	./connection.cpp
	./gamemainmenu.cpp
	./gamemenu.cpp
	./gameview.cpp
	./gameloadingscreen.cpp
	./garagemenu.cpp
	./loadingscreen.cpp
	./main.cpp
	./mainmenu.cpp
	./mainwindow.cpp
	./menucontainer.cpp
	./menu.cpp
	./playerproxy.cpp
	./multiplayermenu.cpp
	./settingsmenu.cpp
	./singleplayermenu.cpp
	./state.cpp
	./updater.cpp
	../views/tableview.cpp
	../models/vehicletablemodel.cpp
	../models/abstractobjecttablemodel.cpp
	../json/json_reader.cpp
	../json/json_value.cpp
	../json/json_writer.cpp
	../net/clientsocket.cpp
	../net/packet.cpp
	../net/serversocket.cpp
	../net/socket.cpp
	../net/socketactivity.cpp
	../net/socketset.cpp
	../sounds/musicplayer.cpp
	../utils/curve.cpp
	../utils/inifile.cpp
	../utils/demangle.cpp
	../utils/directory.cpp
	../utils/outputredirector.cpp
	../exception/exception.cpp
)

set(QT_USE_QTNETWORK 1)

include(../game.cmake)
include(../qt.cmake)
include(../common.cmake)

target_link_libraries(kp2_client audiere)

IF(WIN32)
	target_link_libraries(kp2_client ws2_32)
ENDIF(WIN32)


