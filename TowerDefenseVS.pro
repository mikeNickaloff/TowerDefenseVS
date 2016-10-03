TEMPLATE = app

QT += qml quick widgets


SOURCES += main.cpp \
    src_game/board.cpp \
    src_game/tile.cpp \
    src_game/square.cpp \
    src_game/entrance.cpp \
    src_game/exit.cpp \
    src_game/wall.cpp \
    src_game/tower.cpp \
    src_game/enemy.cpp \
    src_game/entity.cpp \
    src_game/projectile.cpp \
    src_common/game.cpp \
    src_common/map.cpp \
    src_common/player.cpp \
    src_common/team.cpp \
    src_game/path.cpp \
    src_game/paththread.cpp \
    src_game/gun.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src_game/board.h \
    src_game/tile.h \
    src_game/square.h \
    src_game/entrance.h \
    src_game/exit.h \
    src_game/wall.h \
    src_game/tower.h \
    src_game/enemy.h \
    src_game/entity.h \
    src_game/projectile.h \
    src_game/header.h \
    src_game/classes.h \
    src_common/game.h \
    src_common/map.h \
    src_common/player.h \
    src_common/team.h \
    src_game/path.h \
    src_game/paththread.h \
    src_game/gun.h

DISTFILES += \
    LICENSE \
    README.md
