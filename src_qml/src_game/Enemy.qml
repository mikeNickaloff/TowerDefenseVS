import QtQuick 2.0
import com.towerdefensevs 1.0


EntityTemplate {
    id: enemy
    property int enemy_type: 1

    Image {
        anchors.fill: parent
        source: "qrc:///src_images/attackers/"  + enemy_type + ".png"
        id: enemy_image
        Behavior on opacity {
            NumberAnimation { duration: 500 }
        }

    }


    z: 105
     function modifyOpacity(new_opacity) {
         enemy_image.opacity = new_opacity;
         enemy.opacity = 1.0;
     }
    }


