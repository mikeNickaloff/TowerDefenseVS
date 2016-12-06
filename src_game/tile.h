#ifndef TILE_H
#define TILE_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

#include <QPoint>

class Tile : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int col MEMBER m_col NOTIFY colChanged)
    Q_PROPERTY(int row MEMBER m_row NOTIFY rowChanged)
    Q_PROPERTY(bool walkable MEMBER m_walkable NOTIFY walkableChanged)
    Q_PROPERTY(bool buildable MEMBER m_buildable NOTIFY buildableChanged)
    Q_PROPERTY(int width MEMBER m_width NOTIFY myWidthChanged)
    Q_PROPERTY(int height MEMBER m_height NOTIFY heightChanged)
    Q_PROPERTY(int x MEMBER m_x NOTIFY xChanged)
    Q_PROPERTY(int y MEMBER m_y NOTIFY yChanged)
public:
    explicit Tile(QObject *parent = 0, int irow = 0, int icol = 0, int iwidth = 0, int iheight = 0, bool i_buildable = false, bool i_walkable = false);
    int m_row;
    int m_col;
    bool m_buildable;
    bool m_walkable;
    int m_width;
    int m_height;
    int m_x;
    int m_y;
    int distance_to_exit;
    QList<Tile*> neighbors;
QString serialize();
    Q_INVOKABLE QPoint center();
signals:

    void colChanged(int new_col);
    void rowChanged(int new_row);
  Q_SIGNAL  void myWidthChanged(int new_width);
    void heightChanged(int new_height);
    void walkableChanged(int new_walkable);
    void buildableChanged(int new_buildable);
    void xChanged(int new_x);
    void yChanged(int new_y);
public slots:
    void setMyWidth(int new_width);
    void setBuildable(bool new_buildable) { m_buildable = new_buildable; emit this->buildableChanged(new_buildable); }
};

#endif // TILE_H
