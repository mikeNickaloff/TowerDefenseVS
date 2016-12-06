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
        NumberAnimation { duration: rootItem.life * 3 }
    }
    Behavior on y {
        NumberAnimation { duration: rootItem.life * 3 }
    }
    signal done_with_item()
    signal shell_explode(var isplash_distance, var isplash_damage, var idamage, var ix, var iy, var iguntype)
    Timer {
        interval: rootItem.life * 2
        running: true
        repeat: false
        onTriggered: {
            object_done_timer.start();

            rootItem.shell_explode(rootItem.splash_distance, rootItem.splash_damage, rootItem.damage, rootItem.globx, rootItem.globy, 3);
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
    property int life: 200
    ImageParticle {
        id: flame
        objectName: "flame"
        groups: ["flamer"]
        source: "qrc:///src_images/particles/particleflame.png"
        color: "#d39427"
        colorVariation: 0
        alpha: 0.9
        alphaVariation: 0.2
        redVariation: 0.1
        greenVariation: 0
        blueVariation: 0
      //  rotation: 15
        //rotationVariation: 180
        autoRotation: false
        rotationVelocity: 17
        rotationVelocityVariation: 19
        entryEffect: ImageParticle.Scale
        system: particleSystem
    }

    Emitter {
        id: blastEmitter
        objectName: ""

        width: 32
        height: 5
        enabled: true
        group: "flamer"
        emitRate: 15
        maximumEmitted: 8
        startTime: 0
        lifeSpan: 300
        lifeSpanVariation: 100
        size: 38
        sizeVariation: 9
        endSize: 50
        velocityFromMovement: 103
        system: particleSystem
      //  velocity:
          //  PointDirection {
           //    x: 22
           //     xVariation: 11
           //     y: 21
           //     yVariation: 98
          //  }
     //   acceleration:
        //    PointDirection {
              //  x: -71
             //   xVariation: 52
             //   y: -56
              //  yVariation: 51
         //   }
        shape:
            LineShape {
                mirrored: false
            }
    }
    function create_impact() {
        rootItem.height = 25;
        rootItem.width = 5;
        blastEmitter.width = 5;
        blastEmitter.height = 5;
        blastEmitter.size = 25;
        blastEmitter.endSize = 1;
       // blastEmitter.rotation = -45;
       // flame.rotationVariation = 0;

        blastEmitter.lifeSpan = 90;
    }
}
