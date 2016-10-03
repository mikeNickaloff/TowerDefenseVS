import QtQuick 2.7
TileTemplate {
    id: rect

    property int gun_type: 1

    color: "black"
    border.color: "#f9f0f0"
    border.width: 2
    z: 105
    Image {
        anchors.fill: parent
        source: "qrc:///src_images/guns/"  + gun_type + ".png"
    }

    }
