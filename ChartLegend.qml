import QtQuick 2.0

Item {
    id: root
    width: 150
    clip: true
    objectName: "ChartLegend"

    property QtObject source
    property QtObject previousSource

    onSourceChanged: {
        if(previousSource !== null){
            onHowerIndexChanged.disconnect(listHowerIndexChange)
            previousSource.onSlicesChanged.disconnect(updateLegend)
            previousSource.onHoverSliceChanged.disconnect(chartHowerIndexChange)
        }

        if(source.objectName === "PieChartCanvas" || source.objectName === "PolarAreaChartCanvas" ){
            onHowerIndexChanged.connect(listHowerIndexChange)
            source.onSlicesChanged.connect(updateLegend)
            source.onHoverSliceChanged.connect(chartHowerIndexChange)
            list.changingEnabled.connect(pieChartChangeEnabled)
            previousSource = source
            updateLegend()
        } else
            previousSource = null
    }

    signal howerIndexChanged()

    ListView{
        id: list
        anchors.fill: parent
        spacing: 5

        signal changingEnabled(var index, var value)

        highlight: Rectangle{
            color: "gray"
            opacity: 0.4
            radius: 10
        }

        delegate: Item{
            height: 30
            width: parent.width
            Rectangle{
                id: ico
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.margins: 3
                width: height
                color: modelData.color
                radius: 8
                opacity: modelData.enabled?1:0.5
            }

            Text{
                text: modelData.label
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: ico.right
                anchors.margins: 5
                renderType: Text.NativeRendering
                opacity: modelData.enabled?1:0.5
            }

            MouseArea{
                anchors.fill: parent
                hoverEnabled: true && modelData.enabled
                onEntered: {
                    list.currentIndex = model.index
                    root.howerIndexChanged()
                }
                onExited: {
                    list.currentIndex = -1
                    root.howerIndexChanged()
                }
                onClicked:
                    list.changingEnabled(model.index, !modelData.enabled)
            }
        }

        Component.onCompleted: currentIndex = -1
    }

    function chartHowerIndexChange(){
        list.currentIndex = source.currentItem
    }

    function listHowerIndexChange(){
        source.currentItem = list.currentIndex
    }

    function updateLegend(){
        list.model = source.getLegend()
        list.currentIndex = -1
    }

    function pieChartChangeEnabled(index, value){
        source.slices[index].enabled = value
    }
}
