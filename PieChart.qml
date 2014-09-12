import QtQuick 2.0
import BVI.Charts 1.0

Rectangle {
    id: root
    color: "white"
    objectName: "PieChart"

    property alias title: header.text
    property alias titleFont: header.font
    property alias chart: pieChartCanvas
    property alias legend: pieLegend

    Text{
        id: header
        text: "Pie chart"
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 5
        font.pointSize: 20

        renderType: Text.NativeRendering
    }

    PieChartCanvas{
        id: pieChartCanvas
        anchors{
            top: header.bottom
            bottom: parent.bottom
            left: parent.left
            right: legend.left
            margins: 5
        }
        strokeColor: root.color
    }

    ChartLegend{
        id: pieLegend
        anchors{
            margins: 5
            top: header.bottom
            bottom: parent.bottom
            right: parent.right
        }
        source: pieChartCanvas
    }
}
