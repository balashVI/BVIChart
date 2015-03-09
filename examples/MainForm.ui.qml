import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import BVI.Charts 1.0

Item {
    width: 640
    height: 480

    BarChart{
        anchors.fill: parent

        series: [BarSeries{
                data: [2,3,1]
                color: "red"
            }, BarSeries{
                data: [1,2,9]
                color: "blue"
            }, BarSeries{
                data: [6,1,11]
                color: "green"
            }

        ]
    }
}
