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
    ../src/chartpen.cpp \
    ../src/charts_plugin.cpp \
    ../src/piechart.cpp \
    ../src/pieslice.cpp \
    ../src/standartaxis.cpp \
    ../src/polarareachart.cpp \
    ../src/polararea.cpp \
    ../src/polarraxis.cpp \
    ../src/lineseries.cpp \
    ../src/linechart.cpp \
    ../src/chartpoint.cpp \
    ../src/xyseries.cpp \
    ../src/xychart.cpp \
    ../src/bubble.cpp \
    ../src/bubbleseries.cpp \
    ../src/bubblechart.cpp

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
    ../src/chartpen.h \
    ../src/charts_plugin.h \
    ../src/piechart.h \
    ../src/pieslice.h \
    ../src/standartaxis.h \
    ../src/polarareachart.h \
    ../src/polararea.h \
    ../src/polarraxis.h \
    ../src/lineseries.h \
    ../src/linechart.h \
    ../src/chartpoint.h \
    ../src/xyseries.h \
    ../src/xychart.h \
    ../src/bubble.h \
    ../src/bubbleseries.h \
    ../src/bubblechart.h

DISTFILES +=
