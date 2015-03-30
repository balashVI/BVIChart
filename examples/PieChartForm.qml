import QtQuick 2.4
import BVI.Charts 1.0

Rectangle {
    color: "white"

    PieChart{
        anchors.fill: parent
        slices: [
            PieSlice{
                color: "#FF9966"
                value: 10
            },PieSlice{
                color: "#66CCFF"
                value: 20
            },PieSlice{
                color: "blue"
                value: 15
            },PieSlice{
                color: "#7575A3"
                value: 25
            }
        ]
    }
}

