import QtQuick 2.4
import BVI.Charts 1.0

Rectangle {
    color: "grey"

    PolarAreaChart{
        anchors.fill: parent
        polarAreas: [
            PolarArea{
                color: "#D47E6A"
                value: 20
            },PolarArea{
                color: "#66CCFF"
                value: 5
            },PolarArea{
                color: "#7A4A8D"
                value: 18
            },PolarArea{
                color: "#4C996B"
                value: 25
            }
        ]
    }
}

