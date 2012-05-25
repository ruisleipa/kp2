set(editor_UIS
	./ui/mainwindow.ui
)

set(editor_SRCS
	./main.cpp
	./mainwindow.cpp
	../json/json_reader.cpp
	../json/json_value.cpp
	../json/json_writer.cpp
	../utils/curve.cpp
	../views/tableview.cpp
	../models/vehicletablemodel.cpp
	../models/parttablemodel.cpp
	../models/abstractobjecttablemodel.cpp
)

set(game_SRCS
	../game/camshaft.cpp
	../game/charger.cpp
	../game/chassis.cpp
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
	../game/partcontainer.cpp
	../game/player.cpp
	../game/serializable.cpp
	../game/state.cpp
	../game/tire.cpp
	../game/transmission.cpp
	../game/upgrade.cpp
	../game/vehicle.cpp
)

set(editor_MOC_HDRS
	./mainwindow.hpp
	../views/tableview.hpp
	../models/abstractobjecttablemodel.hpp
	../game/object.hpp
	../game/containersignalsandslots.hpp
)

find_package(Qt4 REQUIRED)

add_definitions( -DKP2_EDITOR -DGAME_OBJECTS_QT )

include( ${QT_USE_FILE} )

qt4_wrap_ui( editor_UI_HDRS ${editor_UIS} )

qt4_wrap_cpp( editor_MOC_SRCS ${editor_MOC_HDRS} )

include_directories(../)
include_directories(./)
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/..)

add_executable(kp2_editor  ${editor_SRCS} ${editor_MOC_SRCS} ${game_SRCS} ${editor_UI_HDRS} )

target_link_libraries(kp2_editor ${QT_LIBRARIES})

IF(WIN32)
	add_definitions( -mwindows )
ENDIF(WIN32)


