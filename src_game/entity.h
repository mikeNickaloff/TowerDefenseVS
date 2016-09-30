#ifndef ENTITY_H
#define ENTITY_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class Entity : public QObject
{
    Q_OBJECT
public:
    explicit Entity(QObject *parent = 0);

signals:

public slots:
};

#endif // ENTITY_H
