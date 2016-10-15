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
    ParticleSystem {
        id: particleSystem
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
        interval: 200
        running: false
        repeat: false
        onTriggered: {
            rootItem.done_with_item();
        }
    }
    property int life: 50
    ImageParticle {
        objectName: "fire"
        groups: ["rocket"]
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
        entryEffect: ImageParticle.Fade
        system: particleSystem
    }

    Emitter {
        id: blastEmitter
        objectName: "blast"
        anchors.centerIn: parent
        width: 5
        height: 5
        enabled: true
        group: "rocket"
        emitRate: 40
        maximumEmitted: 20
        startTime: 0
        lifeSpan: 25
        lifeSpanVariation: 0
        size:30
        sizeVariation: 0
        endSize: 5
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
    function create_impact() {
        rootItem.height = 15;
        rootItem.width = 15;
        blastEmitter.width = 25;
        blastEmitter.height = 25;
        blastEmitter.size = 10;
        blastEmitter.endSize = 60;
        blastEmitter.lifeSpan = 100;
    }
}
