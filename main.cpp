#include <QtCore/qglobal.h>
#if QT_VERSION >= 0x050000
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QObject>
#else
#endif
#include <QObject>
#include "src_game/board.h"
#include "src_game/enemy.h"
#include "src_game/entity.h"
#include "src_game/entrance.h"
#include "src_game/exit.h"
#include "src_game/projectile.h"
#include "src_game/square.h"
#include "src_game/tile.h"
#include "src_game/tower.h"
#include "src_game/wall.h"
#include "src_common/game.h"
#include "src_game/gun.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    Game* m_game = new Game;

    QQmlApplicationEngine engine;
engine.rootContext()->setContextProperty("game", m_game);
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
    qmlRegisterType<Gun>("com.towerdefensevs", 1, 0, "Gun");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));







    return app.exec();
}
