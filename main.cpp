#include <QtCore/qglobal.h>
#if QT_VERSION >= 0x050000
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#else
#endif
#include "src_game/header.h"
#include "src_common/game.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<Board>("com.towerdefensevs", 1, 0, "Board");
    qmlRegisterType<Enemy>("com.towerdefensevs", 1, 0, "Enemy");
    qmlRegisterType<Entity>("com.towerdefensevs", 1, 0, "Entity");
    qmlRegisterType<Entrance>("com.towerdefensevs", 1, 0, "Entrance");
    qmlRegisterType<Exit>("com.towerdefensevs", 1, 0, "Exit");
    qmlRegisterType<Projectile>("com.towerdefensevs", 1, 0, "Projectile");
    qmlRegisterType<Square>("com.towerdefensevs", 1, 0, "Square");
    qmlRegisterType<Game>("com.towerdefensevs", 1, 0, "Game");
    qmlRegisterType<Tile>("com.towerdefensevs", 1, 0, "Tile");
    qmlRegisterType<Tower>("com.towerdefensevs", 1, 0, "Tower");
    qmlRegisterType<Wall>("com.towerdefensevs", 1, 0, "Wall");
 engine.load(QUrl(QStringLiteral("qrc:/main.qml")));






    return app.exec();
}
