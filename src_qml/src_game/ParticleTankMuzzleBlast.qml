import QtQuick 2.4
import QtQuick.Particles 2.0

Item {
    id: rootItem
    width: 10
    height: 10
    x: 0
    y: 0
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
    Timer {
        interval: rootItem.life
        running: true
        repeat: false
        onTriggered: {
          rootItem.done_with_item();
        }
    }
    property int life: 100
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
        emitRate: 120
        maximumEmitted: 50
        startTime: 0
        lifeSpan: 70
        lifeSpanVariation: 0
        size: 10
        sizeVariation: 0
        endSize: 50
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
}