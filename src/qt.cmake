find_package(Qt4 REQUIRED)

include(${QT_USE_FILE})

qt4_wrap_ui(${UI} ${UI})

set(CMAKE_AUTOMOC TRUE)
