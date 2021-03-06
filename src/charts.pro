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
    pieslice.cpp \
    xychart.cpp \
    chartheader.cpp \
    chartfont.cpp \
    abstractchart.cpp \
    chartlegend.cpp \
    barchart.cpp \
    abstractseries.cpp \
    barseries.cpp \
    piechart.cpp \
    abstractaxis.cpp \
    categoryaxis.cpp \
    chartpen.cpp \
    standartaxis.cpp

HEADERS += \
    charts_plugin.h \
    pieslice.h \
    xychart.h \
    chartheader.h \
    chartfont.h \
    abstractchart.h \
    chartlegend.h \
    barchart.h \
    abstractseries.h \
    barseries.h \
    piechart.h \
    abstractaxis.h \
    categoryaxis.h \
    chartpen.h \
    standartaxis.h

OTHER_FILES = qmldir

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

