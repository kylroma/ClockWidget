#include "formclock.h"
#include <QtWidgets>

FormClock::FormClock(QWidget *parent) : QWidget(parent), bMove(false)
{
    _pClock = new QLabel;
    _pClock->setAlignment(Qt::AlignHCenter);
    _pClock->setObjectName("clock");

    _pDate = new QLabel;
    _pDate->setAlignment(Qt::AlignHCenter);
    _pDate->setObjectName("date");

    readSettings();

    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->addWidget(_pDate);
    pLayout->addWidget(_pClock);
    setLayout(pLayout);
    
    setStyleClock();

    QTimer *pTimer = new QTimer(this);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(showTime()));
    pTimer->start(1000);
}


void FormClock::setStyleClock()
{
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnBottomHint | Qt::Tool);   
    
    QFile file("StyleClock.css");
    file.open(QFile::ReadOnly);
    QString strCSS = QLatin1String(file.readAll());
    setStyleSheet(strCSS);
}

void FormClock::showTime()
{
    QDateTime dt = QDateTime::currentDateTime();

    _pClock->setText(dt.toString("hh:mm"));
    _pDate->setText(dt.toString("ddd, d MMMM"));
}

void FormClock::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        bMove = true;
        _positionMouse = event->pos();
    }
    else if(event->button() == Qt::MidButton)
        qApp->quit();
}

void FormClock::mouseMoveEvent(QMouseEvent *event)
{
    if((event->buttons() & Qt::LeftButton) && bMove)
          move(event->globalPos() - _positionMouse);
}

void FormClock::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && bMove)
        bMove = false;
}

void FormClock::writeSettings()
{
    qDebug() << _positionWidget.x() << " " << _positionWidget.y();
    _settings.beginGroup("/Settings");
        _settings.setValue("/position", _positionWidget);
    _settings.endGroup();
}

void FormClock::readSettings()
{
    _settings.beginGroup("/Settings");
        _positionWidget = _settings.value("/position", mapToGlobal(QPoint(0, 0))).toPoint();
    _settings.endGroup();
    move(_positionWidget);
}

FormClock::~FormClock()
{
    _positionWidget = mapToGlobal(QPoint(0, 0));
    writeSettings();
}
