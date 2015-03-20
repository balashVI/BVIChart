import QtQuick 2.4
import BVI.Charts 1.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Item {
    anchors.fill: parent
    BarChart{
        anchors.fill: parent
        xAxis.labels: ["first", "second", "third"]
        series: [BarSeries{
                data: [10, 20]
            }


        ]

    }
}

