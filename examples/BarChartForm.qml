import QtQuick 2.4
import BVI.Charts 1.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Rectangle {
    anchors.fill: parent
    color: "white"
    BarChart{
        anchors.fill: parent
        xAxis.labels: ["first", "second", "third", "fourth"]
        series: [BarSeries{
                data: [10, 20, 31]
                color: "#667575A3"
                strokePen.width: 2
                strokePen.color: "#5C5C8A"
            },BarSeries{
                data: [15, 12, 21, 13]
                color: "#bb66CCFF"
                strokePen.width: 2
                strokePen.color: "#5CB8E6"
            },BarSeries{
                data: [25, 22, 11, 3]
                color: "#77FF9966"
                strokePen.width: 2
                strokePen.color: "#CC7A52"
            }
        ]

    }
}

