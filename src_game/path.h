#ifndef PATH_H
#define PATH_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class Tile;
class Path : public QObject
{
    Q_OBJECT
public:
    explicit Path(QObject *parent = 0);
    QList<QPair<int, int> > m_nodes;
signals:

public slots:
    void append_node(int row, int col);
    void clear_path();
};

#endif // PATH_H
