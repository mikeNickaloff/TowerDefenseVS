import QtQuick 2.7
import com.towerdefensevs 1.0
Rectangle {
    property var backend
    function changeWidth(new_width) {
        rect.width = new_width;
    }
    Behavior on width {

        NumberAnimation {
            duration: (20 * backend.tile.col) + (20 * backend.tile.row)

        }
    }
    Component.onCompleted: {
        if (backend !== null) {
            backend.tile.myWidthChanged.connect(changeWidth);


        }
    }
    signal i_have_been_erased();
    function check_if_erased(row, col) {
        if (backend != null) {
            if ((backend.tile.row === row) && (backend.tile.col === col)) {

                i_have_been_erased();
            }
        }
    }

    property var isDragModeOn: false
    property var offset_start_x: 0
    property var offset_start_y: 0
    property var old_bg_x_translation: 0
    property var old_bg_y_translation: 0
    property var bg_x_translation;
    property var bg_y_translation;
    signal x_translate_changed(var new_x_translate)
    signal y_translate_changed(var new_y_translate)
    signal restart_animation_translate()

    MouseArea {
        anchors.fill: parent
        width: parent.width
        height: parent.height
        onClicked: {
            console.log("walkable: " + backend.tile.walkable );
            backend.gotMouseClick();
        }
        z: 101







        onPressed: {
            isDragModeOn = true;
            offset_start_x = mouseX;
            offset_start_y = mouseY;
            old_bg_x_translation = 0;
            old_bg_y_translation = 0;

        }
        onPositionChanged:  {
            if (isDragModeOn == true) {
                var new_bg_x_translation;
                var new_bg_y_translation;
                new_bg_x_translation = (0.25 * (mouseX - offset_start_x));
                new_bg_y_translation = (0.25 * (mouseY - offset_start_y));
                if ((Math.abs(new_bg_x_translation) > 3) || (Math.abs(new_bg_y_translation) > 3)) {
                    //hide_chooser_mode = true;
                    bg_x_translation = old_bg_x_translation + new_bg_x_translation;
                    bg_y_translation = old_bg_y_translation + new_bg_y_translation;
                    game.board.changed_xy_board_translation(bg_x_translation, bg_y_translation);
                    //y_translate_changed(bg_y_translation);
                    //restart_animation_translate()

                }
            }
        }
        onReleased:  {
            isDragModeOn = false;
            // hide_chooser_mode = false;
        }
    }

}
