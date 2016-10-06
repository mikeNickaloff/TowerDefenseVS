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
           duration: 2000
        }
    }
    Image {
        id: gunImage
        anchors.fill: parent
        source: "qrc:///src_images/guns/"  + gun_type + ".png"
        Behavior on rotation {
            NumberAnimation { duration: 2000 }
        }
    }
    function setRotation(newRot) {
        gunImage.rotation = newRot;
    }

    }
