import QtQuick 2.4
import QtQuick.Layouts 1.1

Rectangle {
    anchors.fill: parent
    GridLayout{
        anchors.fill: parent
        columns: 3
        LineChartForm{
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        BarChartForm{
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        PieChartForm{
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        PolarAreaChartForm{
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}

