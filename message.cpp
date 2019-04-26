#include "message.h"

Message::Message(): QMessageBox()
{
    timeout = 10;
    currentTime = 0;
    this->setWindowFlags(Qt::FramelessWindowHint);

    this->setStandardButtons(0);
    this->setText("BRAVO");
    QString string = "Fin dans "+QString::number(timeout);
    this->setInformativeText(string);
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
