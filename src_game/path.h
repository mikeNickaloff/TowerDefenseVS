#ifndef PATH_H
#define PATH_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class Tile;
class Board;
class Path : public QObject
{
    Q_OBJECT
public:
    explicit Path(QObject *parent = 0, Board* i_board = 0);
    QList<QPair<int, int> > m_nodes;
    Board* m_board;
signals:

public slots:
    void append_node(int row, int col);
    void clear_path();
    void simplify();
};

#endif // PATH_H
