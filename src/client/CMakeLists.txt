set(client_UIS
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
	./ui/technicsmenu.ui
)

set(client_SRCS
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
	./abstractobjecttablemodel.cpp
	./tableview.cpp
	./playerproxy.cpp
	./parttablemodel.cpp
	./multiplayermenu.cpp
	./settingsmenu.cpp
	./singleplayermenu.cpp
	./state.cpp
	./technicsmenu.cpp
	./updater.cpp
	./vehicletablemodel.cpp
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
	../utils/inifile.cpp
	../utils/demangle.cpp
	../utils/directory.cpp
	../utils/outputredirector.cpp
	../exception/exception.cpp
)

set(game_SRCS
	../game/camshaft.cpp
	../game/charger.cpp
	../game/clutch.cpp
	../game/cooler.cpp
	../game/cylinderhead.cpp
	../game/differential.cpp
	../game/engine.cpp
	../game/exhaustmanifold.cpp
	../game/exhaustpipe.cpp
	../game/fuelintake.cpp
	../game/fuelpump.cpp
	../game/injector.cpp
	../game/intakemanifold.cpp
	../game/object.cpp
	../game/objectfactory.cpp
	../game/part.cpp
	../game/player.cpp
	../game/serializable.cpp
	../game/state.cpp
	../game/tire.cpp
	../game/transmission.cpp
	../game/upgrade.cpp
	../game/vehicle.cpp
)

set(client_MOC_HDRS
	./carshopmenu.hpp
	./abstractobjecttablemodel.hpp
	./connection.hpp
	./gamemenu.hpp
	./gamemainmenu.hpp
	./gameloadingscreen.hpp
	./gameview.hpp
	./garagemenu.hpp
	./loadingscreen.hpp
	./mainmenu.hpp
	./mainwindow.hpp
	./menu.hpp
	./menucontainer.hpp
	./multiplayermenu.hpp
	../game/object.hpp
	../game/container.hpp
	./settingsmenu.hpp
	./singleplayermenu.hpp
	./technicsmenu.hpp
	./tableview.hpp
	./updater.hpp
)

find_package(Qt4 REQUIRED)

set(QT_USE_QTNETWORK 1)

add_definitions( -DKP2_CLIENT )

include( ${QT_USE_FILE} )

qt4_wrap_ui( client_UI_HDRS ${client_UIS} )

qt4_wrap_cpp( client_MOC_SRCS ${client_MOC_HDRS} )

include_directories(../)
include_directories(./)
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/..)

add_executable(kp2_client  ${client_SRCS} ${client_MOC_SRCS} ${game_SRCS} ${client_UI_HDRS} )

target_link_libraries(kp2_client ${QT_LIBRARIES} audiere) 

IF(WIN32)
	target_link_libraries(kp2_client ws2_32)	
	add_definitions( -mwindows )
ENDIF(WIN32)


