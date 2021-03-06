#ifndef ENTITY_H
#define ENTITY_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QPoint>
#include <QtMath>
class Board;
class Tile;
class Path;
class Entity : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int width MEMBER m_width NOTIFY myWidthChanged)
    Q_PROPERTY(int height MEMBER m_height NOTIFY heightChanged)
    Q_PROPERTY(int x MEMBER m_x NOTIFY xChanged)
    Q_PROPERTY(int y MEMBER m_y NOTIFY yChanged)
public:
    explicit Entity(QObject *parent = 0, Board* i_board = 0);
    int m_width;
    int m_height;
    int m_x;
    int m_y;
    Path* m_path;
    Board* m_board;
    int m_speed;
    int m_entityIndex;
    bool completed;
    Q_INVOKABLE QPoint center();
    Q_INVOKABLE QPoint realpos();
    QPoint _realpos;

    qreal m_opacity;
    qreal  angleTo(int cx, int cy, int ex, int ey) {
       qreal dy = ey - cy;
       qreal dx = ex - cx;
        qreal theta = qAtan2(dy, dx); // range (-PI, PI]
        theta *= 180 / (22 / 7); // rads to degs, range (-180, 180]
        return (360 + theta);
    }

signals:
    Q_SIGNAL  void myWidthChanged(int new_width);
      void heightChanged(int new_height);
      void xChanged(int new_x);
      void yChanged(int new_y);
      void completed_path(int entityIndex);
      void callout_position(QPoint oldPos, QPoint newPos);
      void killed(int entityIndex);
      void opacityChanged(qreal new_opacity);
      void rotationChanged(qreal newRot);
public slots:
      void set_x(int new_x) { m_x = new_x; emit xChanged(new_x); }
      void set_y(int new_y) { m_y = new_y; emit yChanged(new_y); }
      void next_path_tile();
};

#endif // ENTITY_H
