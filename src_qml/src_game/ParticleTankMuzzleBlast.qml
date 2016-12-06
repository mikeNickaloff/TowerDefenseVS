import QtQuick 2.4
import QtQuick.Particles 2.0

Item {
    id: rootItem
    width: 10
    height: 10
    x: 0
    y: 0
    property int globx;
    property int globy;
    property int splash_damage
    property int splash_distance
    property int damage

    Behavior on x {
        NumberAnimation { duration: rootItem.life }
    }
    Behavior on y {
        NumberAnimation { duration: rootItem.life }
    }

    signal done_with_item()
    signal shell_explode(var isplash_distance, var isplash_damage, var idamage, var ix, var iy, var iguntype)
    Timer {
        interval: rootItem.life
        running: true
        repeat: false
        onTriggered: {
            object_done_timer.start();
            rootItem.shell_explode(rootItem.splash_distance, rootItem.splash_damage, rootItem.damage, rootItem.globx, rootItem.globy, 1);
            create_impact();
        }
    }
    Timer {
        id: object_done_timer
        interval: 400
        running: false
        repeat: false
        onTriggered: {
            rootItem.done_with_item();
        }
    }
    function create_impact() {
        rootItem.height = 5;
        rootItem.width = 5;
        blastEmitter.width = 4;
        blastEmitter.height = 4;
        blastEmitter.size = 10;
        blastEmitter.endSize = 120;
        blastEmitter.lifeSpan = 500;
    }
    property int life: 150
    ParticleSystem {
        id: particleSystem

        ImageParticle {
            objectName: "fire"
            groups: ["lit"]
            source: "qrc:///src_images/particles/particleA.png"
            color: "#ffc020"
            colorVariation: 0
            alpha: 1
            alphaVariation: 0
            redVariation: 0
            greenVariation: 0
            blueVariation: 0
            rotation: 0
            rotationVariation: 0
            autoRotation: false
            rotationVelocity: 0
            rotationVelocityVariation: 0
           // entryEffect: ImageParticle.Fade
            system: particleSystem
        }

        Emitter {
            id: blastEmitter
            objectName: "blast"
            anchors.centerIn: parent
            width: 2
            height: 2
            enabled: true
            group: "lit"
            emitRate: 10
            maximumEmitted: 20
            startTime: 0
            lifeSpan: 320
            lifeSpanVariation: 0
            size:10
            sizeVariation: 0
            endSize: 1
            velocityFromMovement: 0
            system: particleSystem
            velocity:
                CumulativeDirection {}
            acceleration:
                PointDirection {
                x: 0
                xVariation: 16
                y: 0
                yVariation: 17
            }
            shape:
                EllipseShape {
                fill: true
            }

        }


        ParticleGroup {
            name: "lit"
            duration: 10000

            TrailEmitter {
                id: fireballFlame
                group: "flame"

                emitRatePerParticle: 18
                lifeSpan: 500
                emitWidth: 8
                emitHeight: 8

                size: 16
                sizeVariation: 0
                endSize: 10
            }
            system: particleSystem
            TrailEmitter {
                id: fireballSmoke
                group: "smoke"
                // ![lit]

                emitRatePerParticle: 20
                lifeSpan: 700
                emitWidth: 16
                emitHeight: 16

                velocity: PointDirection {yVariation: 16; xVariation: 16}
                acceleration: PointDirection {y: -16}

                size: 24
                sizeVariation: 8
                endSize: 8
            }
        }

        ImageParticle {
            id: smoke
            anchors.fill: parent
            groups: ["smoke"]
            source: "qrc:///particleresources/glowdot.png"
            colorVariation: 0
            color: "#00111111"
        }
        ImageParticle {
            id: pilot
            anchors.fill: parent
            groups: ["pilot"]
            source: "qrc:///src_images/particles/rocketbacklit.png"
            redVariation: 0.01
            blueVariation: 0.4
            color: "#0010004f"
        }
        ImageParticle {
            id: flame
            anchors.fill: parent
            groups: ["flame", "lit", "lighting"]
            source: "qrc:///src_images/particles/particleA.png"
            colorVariation: 0.1
            color: "#00ff400f"
        }
    }
}
