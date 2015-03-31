TEMPLATE = app

CONFIG += c++11

QT += qml quick widgets

SOURCES += main.cpp \
    ../src/abstractaxis.cpp \
    ../src/abstractchart.cpp \
    ../src/abstractseries.cpp \
    ../src/barchart.cpp \
    ../src/barseries.cpp \
    ../src/categoryaxis.cpp \
    ../src/chartfont.cpp \
    ../src/chartpen.cpp \
    ../src/charts_plugin.cpp \
    ../src/piechart.cpp \
    ../src/pieslice.cpp \
    ../src/standartaxis.cpp \
    ../src/xychart.cpp \
    ../src/polarareachart.cpp \
    ../src/polararea.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    ../src/abstractaxis.h \
    ../src/abstractchart.h \
    ../src/abstractseries.h \
    ../src/barchart.h \
    ../src/barseries.h \
    ../src/categoryaxis.h \
    ../src/chartfont.h \
    ../src/chartpen.h \
    ../src/charts_plugin.h \
    ../src/piechart.h \
    ../src/pieslice.h \
    ../src/standartaxis.h \
    ../src/xychart.h \
    ../src/polarareachart.h \
    ../src/polararea.h
