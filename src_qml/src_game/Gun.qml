import QtQuick 2.7
TileTemplate {
    id: rect
    property var background
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
           duration: 200
        }
    }
    Image {
        id: gunImage
        anchors.fill: parent
        source: "qrc:///src_images/guns/"  + gun_type + ".png"
        Behavior on rotation {
            NumberAnimation { duration: 200 }
        }
    }
    function setRotation(newRot) {
        gunImage.rotation = newRot;
    }
    function fire_type_1(endX, endY, i_type, i_duration) {
        var component = Qt.createComponent("qrc:///src_qml/src_game/ParticleTankMuzzleBlast.qml");
        var sq = component.createObject(rect, { "x" : mapFromItem(background, backend.tile.center().x, backend.tile.center().y).x, "y" : mapFromItem(background, backend.tile.center().x, backend.tile.center().y).y, "life" : i_duration });
        sq.x = mapFromItem(background, endX, endY).x;
        sq.y = mapFromItem(background, endX, endY).y;
        sq.width = 10;
        sq.height = 10;
        sq.z = 600;
        sq.visible = true;
        sq.done_with_item.connect(sq.destroy);

    }
    }
