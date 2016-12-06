import QtQuick 2.0
import QtQuick.Particles 2.0
Item {


    ParticleGroup {
        name: "lit"
        duration: 10000
        onEntered: score++;
        TrailEmitter {
            id: fireballFlame
            group: "flame"

            emitRatePerParticle: 38
            lifeSpan: 200
            emitWidth: 8
            emitHeight: 8

            size: 24
            sizeVariation: 0
            endSize: 4
        }

        TrailEmitter {
            id: fireballSmoke
            group: "smoke"
            // ![lit]

            emitRatePerParticle: 120
            lifeSpan: 2000
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
        source: "qrc:///particleresources/glowdot.png"
        redVariation: 0.01
        blueVariation: 0.4
        color: "#0010004f"
    }
    ImageParticle {
        id: flame
        anchors.fill: parent
        groups: ["flame", "lit", "lighting"]
        source: "qrc:///src_images/particles/particleflame.png"
        colorVariation: 0.1
        color: "#00ff400f"
    }
}
