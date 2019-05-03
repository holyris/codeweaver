#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QWidget>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <iostream>
#include <unistd.h>

class Message : public QMessageBox
{

private:
    int timeout, currentTime;
public:
    Message(int timeout);
    ~Message();
    void showEvent ( QShowEvent *event );
    void timerEvent ( QTimerEvent *event );

};

#endif // MESSAGE_H
