#include "message.h"

Message::Message(int timeout): QMessageBox()
{
    this->timeout = timeout;
    currentTime = 0;
//    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowFlags(Qt::CustomizeWindowHint);


    this->setStandardButtons(0);
    QString string = "Fin dans "+QString::number(timeout);
    this->setInformativeText(string);

    int nWidth = 300;
    int nHeight = 400;

    this->resize(nWidth, nHeight);
}

Message::~Message()
{

}

void Message::showEvent( QShowEvent *event ) {
    currentTime = 0;
    this->startTimer(1000);

}

void Message::timerEvent(QTimerEvent *event)
{

    currentTime++;
    QString string = "Fin dans " + QString::number(timeout-currentTime);
    this->setInformativeText(string);
    if (currentTime>timeout) {
        this->done(0);
    }
}
