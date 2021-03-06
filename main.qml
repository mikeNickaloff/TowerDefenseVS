import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import com.towerdefensevs 1.0
import "./src_qml/src_js/BackendLogic.js" as BackendLogic
import "./src_qml/src_js/FrontEndLogic.js" as FrontEndLogic

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    color: "black"
    property var m_squares: []



    Component.onCompleted: {

        game.createBoard();



        // dynamic object creation
        game.board.signal_square_added.connect(BackendLogic.create_square);
        game.board.signal_entrance_added.connect(BackendLogic.create_entrance);
        game.board.signal_exit_added.connect(BackendLogic.create_exit);
        game.board.signal_wall_added.connect(BackendLogic.create_wall);
        game.board.signal_gun_added.connect(BackendLogic.create_gun);
        FrontEndLogic.init_grid(50, 50);

        game.board.signal_update_pathing_grid.connect(FrontEndLogic.init_grid);
        game.board.signal_get_shortest_path.connect(FrontEndLogic.get_shortest_path);
        game.board.signal_get_shortest_target_path.connect(FrontEndLogic.get_shortest_path);

        //             game.board.signal_pathing_set_walkable.connect(FrontEndLogic.set_grid_node_walkable);
        // create map
        game.createMap();

        // initialize grid



        // pathing logic connections


        //FrontEndLogic.init_grid(game.board.numRows, game.board.numColumns);


        //game.board.update_walkable_states();






        //   FrontEndLogic.get_shortest_path(0,0, 10, 10);
        //create paths
        //  game.board.populate_entry_paths();

        game.board.signal_update_xy_translation.connect(update_xy_translation_slot);
        animation_rotate_scene.start();


        game.board.signal_enemy_added.connect(BackendLogic.create_enemy);
        game.board.populate_entry_paths();

        game.board.signal_show_gunStore.connect(BackendLogic.show_gunStore);
        game.board.signal_show_upgrade_store.connect(BackendLogic.show_upgradeStore);
        game.moneyChanged.connect(scoreHUD.change_money);
        game.levelChanged.connect(scoreHUD.change_level);

    }

    function update_xy_translation_slot(new_x, new_y) {
        bg_x_translation += new_x;
        bg_y_translation += new_y;
        animation_translate_scene.restart();
    }
    SequentialAnimation {
        id: animation_rotate_scene
        RotationAnimation {
            to: 20
            duration: 1000
            target: sceneRotation
            property: "angle"
            easing.type: Easing.InOutQuad
        }
        /* RotationAnimation {
            to: 20
            duration: 1000
            target: particleSceneRotation
            property: "angle"
            easing.type: Easing.InOutQuad
        } */
    }
    ParallelAnimation {
        id: animation_translate_scene
        NumberAnimation {
            to: bg_x_translation
            duration: 100
            target: sceneTranslation
            property: "x"
        }
        NumberAnimation {
            to: bg_y_translation
            duration: 100
            target: sceneTranslation
            property: "y"
        }

    }
    property var bg_x_translation: 0
    property var bg_y_translation: 0
    Item {
        id: background
        width: Screen.desktopAvailableWidth * 0.85
        height: Screen.desktopAvailableHeight * 0.85 * 0.95
        Rectangle {
            color: "black"
            anchors.fill: parent
            z: 0
        }
        transform: [
            Rotation {
                id: sceneRotation
                axis.x: 1
                axis.y: 0
                axis.z: 0
                origin.x: width / 2
                origin.y: height / 2
            },
            Translate {
                id: sceneTranslation
                x: bg_x_translation
                y: bg_y_translation
            }
        ]



        anchors.top: scoreHUD.bottom







    }

    Rectangle {
        id: scoreHUD
        height: background.height * 0.05
        width: background.width
        x: 0
        y: 0
        function change_money(newAmt) {
            game_money = newAmt;
            moneyText.text = "Money: $" + newAmt;
        }
        function change_level(newAmt) {
            game_level = newAmt;
            levelText.text = "Level: " + newAmt;
        }
        property int game_money: 4000
        property int game_level: 1

        color: "transparent"
        Item {
            Row {
                Text {
                    id: moneyText
                    text: "Money: $" + scoreHUD.game_money
                    font.family: "Consolas"
                    horizontalAlignment: Text.AlignHCenter
                    style: Text.Raised
                    font.pointSize: 12
                    width: 200
                    styleColor: "#0aec28"

                    color: "#0aec28"
                }
                Text {
                    id: levelText
                    text: "Level: " + scoreHUD.game_level
                    font.family: "Consolas"
                    horizontalAlignment: Text.AlignHCenter
                    style: Text.Raised
                    font.pointSize: 12
                    width: 200
                    styleColor: "#0aec28"

                    color: "#0aec28"
                }

            }
        }
    }
    Rectangle {
        id: gunStore
        height: background.height * 0.20
        width: background.width * 0.90
        anchors.bottom: parent.bottom
        z: 500
        color: "#3ddb4a"
        visible: false
        enabled: false
        GroupBox {
            anchors.fill: parent
            RowLayout {
                spacing: 3

                Button {
                    text: "cannon\n$250"
                    onClicked: {
                        game.board.place_gun_on_selected(1);
                    }
                }
                Button {
                    text: "Machine Gun\n$250"
                    onClicked: {
                        game.board.place_gun_on_selected(2);
                    }
                }

                Button {
                    text: "Flame Tower\n$250"
                    onClicked: {
                        game.board.place_gun_on_selected(3);
                    }
                }

            }
        }
    }


    Rectangle {
        id: upgradeStore
        height: background.height * 0.20
        width: background.width * 0.90
        anchors.bottom: parent.bottom
        z: 500
        color: "#2d7ae4"
        border.color: "#938b8b"
        visible: false
        enabled: false
        property var i_row;
        property var i_col;
        property var i_damage;
        property var i_range;
        property var i_reload;
        property var i_rate;

        GridView {
            anchors.left: parent.left
            width: parent.width * 0.66
            height: parent.height

            cellHeight: background.height * 0.09
            cellWidth: background.width * 0.65
            model: VisualItemModel {
                Row {
                    spacing: background.width * 0.05
                    Text {
                        text: "Damage: " + upgradeStore.i_damage;
                        color: "#fbf8f8"
                        font.family: "Consolas"
                        styleColor: "#f9f2f2"
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 14
                    }
                    Text {
                        text: " -> " + upgradeStore.damage_new_amount();
                        color: "#fbf8f8"
                        font.family: "Consolas"
      //                  horizontalAlignment: Text.AlignHCenter
                        styleColor: "#f9f2f2"
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 14
                    }

                    Text {

                        text: "[$" + upgradeStore.damage_cost() + "]"
                        color: "#fbf8f8"
                        font.family: "Consolas"
    //                    horizontalAlignment: Text.AlignRight
                        styleColor: "#f9f2f2"
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 14
                    }

                }
                Row {
                            spacing: background.width * 0.10
                    Text {
                        text: "Range: " + upgradeStore.i_range;
                        color: "#fbf8f8"
                        font.family: "Consolas"
                        styleColor: "#f9f2f2"
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 14
                    }
                    Text {
                        text: " -> " + upgradeStore.range_new_amount();
                        color: "#fbf8f8"
                        font.family: "Consolas"
//                        horizontalAlignment: Text.AlignHCenter
                        styleColor: "#f9f2f2"
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 14
                    }

                    Text {
                        text: "[$" + upgradeStore.range_cost() + "]"
                        color: "#fbf8f8"
                        font.family: "Consolas"
  //                      horizontalAlignment: Text.AlignRight
                        styleColor: "#f9f2f2"
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 14
                    }
                }
            }
        }

        GridView {
            anchors.left: parent.horizontalCenter;
            width: parent.width * 0.25
            height: parent.height

            cellHeight: background.height * 0.09
            cellWidth: background.width * 0.25
            model: VisualItemModel {
                Row {
                    Button {
                        text: "Upgrade"
                        onClicked: function()  { game.board.upgrade_selected_gun_damage(upgradeStore.damage_new_amount(), upgradeStore.damage_cost()); }
                    }

                }
                Row {

                    Button {
                        text: "Upgrade"
                         onClicked: function()  { game.board.upgrade_selected_gun_range(upgradeStore.range_new_amount(), upgradeStore.range_cost()); }
                    }
                }
            }
        }

        function range_cost() {
            return Math.max(Math.round((upgradeStore.i_range * 1.25) / (upgradeStore.i_rate * 0.1)), 250);
        }

        function damage_cost() {
            return Math.max(Math.round((upgradeStore.i_damage * 1.75) / (upgradeStore.i_reload * 0.01)), 300);
        }
        function range_new_amount() {
            return Math.max(Math.round(upgradeStore.i_range * 1.13), Math.round(upgradeStore.i_range + 10));
        }

        function damage_new_amount() {
            return Math.max(Math.round(upgradeStore.i_damage * 1.13), (upgradeStore.i_damage + 15));
        }
    }



}
