#ifndef FORMCLOCK_H
#define FORMCLOCK_H

#include <QLabel>
#include <QSettings>

class FormClock : public QWidget
{
    Q_OBJECT
private:
    QLabel *_pClock;
    QLabel *_pDate;
    QPoint _positionWidget;
    QPoint _positionMouse;
    bool bMove;
    QSettings _settings;
public:
    explicit FormClock(QWidget *parent = 0);
    ~FormClock();
    void setStyleClock();

    void writeSettings();
    void readSettings();
protected:
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
signals:

public slots:
    void showTime();
};

#endif // FORMCLOCK_H
