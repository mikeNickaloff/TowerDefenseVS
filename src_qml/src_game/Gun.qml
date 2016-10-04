import QtQuick 2.7
TileTemplate {
    id: rect

    property int gun_type: 1

    color: "black"
    border.color: "#f9f0f0"
    border.width: 2
    z: 105
    opacity: 0
    Behavior on opacity {
        OpacityAnimator {
           from: 0
           to: 1
           duration: 10000
        }
    }
    Image {
        anchors.fill: parent
        source: "qrc:///src_images/guns/"  + gun_type + ".png"
    }

    }
