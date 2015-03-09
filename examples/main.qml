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
                text: qsTr("Стовпчикковий графік")
                onTriggered: loader.source = "BarChartForm.ui.qml";
            }
        }
        Menu{
            title: qsTr("Засоби")
            MenuItem{
                text: qsTr("Властивості графіка")
                onTriggered: loader.item.openDialog();
            }
        }
    }

    Loader {
        id: loader
        anchors.fill: parent
        active: true
        source: "BarChartForm.qml"
    }
}
