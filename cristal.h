#ifndef CRISTAL_H
#define CRISTAL_H

#include <QObject>
#include <QWidget>
#include <QGraphicsPixmapItem>
#include <iostream>
class Cristal: public QGraphicsPixmapItem
{
public:
    Cristal();
    ~Cristal();
    void set(unsigned int x, unsigned int y);
    void destroy();
    void reset();
};

#endif // CRISTAL_H
