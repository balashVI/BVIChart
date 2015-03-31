import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2

ApplicationWindow {
    title: qsTr("Hello World")
    width: 640
    height: 480
    visible: true

    menuBar: MenuBar {
        Menu {
            title: qsTr("&Тип графіка")
            MenuItem {
                text: qsTr("AllCharts")
                onTriggered: loader.source = "AllChartsForm.qml"
            }
            MenuItem {
                text: qsTr("BarChart")
                onTriggered: loader.source = "BarChartForm.qml"
            }
            MenuItem {
                text: qsTr("PieChart")
                onTriggered: loader.source = "PieChartForm.qml"
            }
        }
    }

    Loader {
        id: loader
        anchors.fill: parent
        active: true
        source: "AllChartsForm.qml"
    }
}
