import QtQuick 2.0
import com.towerdefensevs 1.0


EntityTemplate {
    id: enemy
    property int enemy_type: 1
    Image {
        anchors.fill: parent
        source: "qrc:///src_images/attackers/"  + enemy_type + ".png"
    }


    z: 105
    }


