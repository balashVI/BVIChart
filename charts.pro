TEMPLATE = lib
TARGET = Charts
QT += qml quick
CONFIG += qt plugin

QMAKE_CXXFLAGS += -std=c++11

TARGET = $$qtLibraryTarget($$TARGET)
uri = BVI.Charts

# Input
SOURCES += \
    charts_plugin.cpp \
    piechartcanvas.cpp \
    polarareachartcanvas.cpp \
    chartcanvas.cpp \
    chartpopup.cpp \
    charttoolkit.cpp \
    chartaxis.cpp \
    pieslice.cpp

HEADERS += \
    charts_plugin.h \
    piechartcanvas.h \
    polarareachartcanvas.h \
    chartcanvas.h \
    chartpopup.h \
    charttoolkit.h \
    chartaxis.h \
    pieslice.h

OTHER_FILES = qmldir \
    PieChart.qml \
    ChartLegend.qml \
    PolarAreaChart.qml \
    changelog.txt

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

