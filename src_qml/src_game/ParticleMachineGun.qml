import QtQuick 2.4
import QtQuick.Particles 2.0

Item {
    objectName: "Particle scene"
    width: 5
    height: 5
    id: rootItem
    x: 0
    y: 0
    z: 900
    property int globx;
    property int globy;
    property int splash_damage
    property int splash_distance
    property int damage
    property int dx;
    property int dy;

    ParticleSystem {
        id: particleSystem
    }
    Behavior on x {
        NumberAnimation { duration: rootItem.life }
    }
    Behavior on y {
        NumberAnimation { duration: rootItem.life }
    }
    signal done_with_item()
    signal shell_explode(var isplash_distance, var isplash_damage, var idamage, var ix, var iy)
    Timer {
        interval: rootItem.life
        running: true
        repeat: false
        onTriggered: {
            object_done_timer.start();

            rootItem.shell_explode(rootItem.splash_distance, rootItem.splash_damage, rootItem.damage, rootItem.globx, rootItem.globy);
            create_impact();
        }
    }
    Timer {
        id: object_done_timer
        interval: 100
        running: false
        repeat: false
        onTriggered: {
            rootItem.done_with_item();
        }
    }
    property int life: 40


    ImageParticle {
        objectName: "machineGunMuzzle"
        groups: ["machineGunFlash"]
        source: "qrc:///src_images/particles/tracer.png"
        color: "#ffd605"
        colorVariation: 0
        alpha: 1
        alphaVariation: 0
        redVariation: 0
        greenVariation: 0
        blueVariation: 0
        rotation: 90
        rotationVariation: 0
        autoRotation: false
        rotationVelocity: 0
        rotationVelocityVariation: 0
        entryEffect: ImageParticle.None
        system: particleSystem
    }

    ImageParticle {
        id: bulletParticle
        objectName: "machineGunProjectile"
        groups: ["machineGunBullet"]
        source: "qrc:///src_images/particles/tracer.png"
        color: "#ffce0a"
        colorVariation: 0
        alpha: 1
        alphaVariation: 0
        redVariation: 0
        greenVariation: 0
        blueVariation: 0
        rotation: 90
        rotationVariation: 0
        autoRotation: false
        rotationVelocity: 0
        rotationVelocityVariation: 0
        entryEffect: ImageParticle.None
        system: particleSystem
    }

    Emitter {
        objectName: "MuzzleFlash"

        width: 5
        height: 1
        enabled: true
        group: "machineGunFlash"
        emitRate: 7
        maximumEmitted: 8
        startTime: 40
        lifeSpan: 50
        lifeSpanVariation: 10
        size:23
        sizeVariation: 5
        endSize: 4
        velocityFromMovement: 0
        system: particleSystem
        velocity:
            PointDirection {
                x: 0
                xVariation: 0
                y: 0
                yVariation: 0
            }
        acceleration:
            PointDirection {
                x: 0
                xVariation: 0
                y: 0
                yVariation: 0
            }
        shape:
            RectangleShape {}
    }

    Emitter {
        z: 900
        id: blastEmitter
        objectName: "bulletEmitter"
        width: 5
        height: 5
        y: 0
        enabled: true
        group: "machineGunBullet"
        emitRate: 10
        maximumEmitted: 3
        startTime: 35
        lifeSpan: 35
        lifeSpanVariation: 0
        size: 23
        sizeVariation: 0
        endSize: 3
        velocityFromMovement: 0
        system: particleSystem
        velocity:
            PointDirection {
                x: 0
                xVariation: 0
                y: 0
                yVariation: 0
            }
        acceleration:
            PointDirection {
                x: 0
                xVariation: 0
                y: 0
                yVariation: 0
            }
        shape:
            RectangleShape {}
    }
    function create_impact() {
        rootItem.height = 15;
        rootItem.width = 15;
        blastEmitter.width = 5;
        blastEmitter.height = 5;
        blastEmitter.size = 15;
        blastEmitter.endSize = 1;
        blastEmitter.rotation += 90;
        bulletParticle.rotationVariation = 90;

        blastEmitter.lifeSpan = 100;
    }
}
