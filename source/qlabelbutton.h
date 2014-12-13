#ifndef QLABELBUTTON_H
#define QLABELBUTTON_H

#include <QLabel>

class QLabelButton : public QLabel
{
    Q_OBJECT

public:
    explicit QLabelButton(QWidget *parent = 0);
    ~QLabelButton();

signals:
    void clicked(QMouseEvent *ev);

protected:
    void mouseReleaseEvent(QMouseEvent *ev);

public slots:

};

#endif // QLABELBUTTON_H
