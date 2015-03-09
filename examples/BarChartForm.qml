import QtQuick 2.4
import BVI.Charts 1.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Item {
    function openDialog(){
        dialog.open();
    }

    anchors.fill: parent
    BarChart{
        anchors.fill: parent
        series: [BarSeries{

            }

        ]

    }

    Dialog{
        id: dialog
        title: qsTr("BarChart options")
        visible: true
        contentItem: Rectangle {
                id: dialogRoot
                implicitWidth: 200
                implicitHeight: 500
                ScrollView{
                    anchors.fill: parent

                    contentItem: ColumnLayout{
                        width: dialogRoot.width
                        GroupBox{
                            Layout.fillWidth: true
                            title: qsTr("Header")
                            GridLayout{
                                columns: 2
                                anchors.fill: parent
                                Text{text:qsTr("Text")}
                                TextField{
                                    Layout.column: 1
                                    Layout.fillWidth: true
                                }
                            }
                        }
                    }
                }
            }
    }
}

