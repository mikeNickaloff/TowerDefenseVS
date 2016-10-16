import QtQuick 2.7
import com.towerdefensevs 1.0


Rectangle {
    id: rect
    color: "transparent"
    property var backend
    property var xpos
    property var ypos

    function changeX(new_x) {
       rect.x = new_x;
    }
    function changeY(new_y) {
        rect.y = new_y;
    }
    Behavior on x {

        NumberAnimation {


            duration: backend.speed

        }

   }
    Behavior on y {

        NumberAnimation {
            duration: backend.speed


        }
    }

    Behavior on rotation {
        NumberAnimation {
            duration: 200
        }
    }

    Component.onCompleted: {
        if (backend !== null) {
          backend.entity.xChanged.connect(changeX);
          backend.entity.yChanged.connect(changeY);
          backend.entity.rotationChanged.connect(changeRot);
          //  backend.entity.next_path_tile();
            //console.log("Moving to next tile");

        }
    }
    signal i_have_been_erased();
    function check_if_erased(object) {
        if (backend != null) {
            if (backend == object)

                i_have_been_erased();
            }
        }

    function changeRot(newRot) {
        rect.rotation = newRot;
    }
    }


