#include "qlabelbutton.h"

QLabelButton::QLabelButton(QWidget *parent) :
    QLabel(parent)
{
}

QLabelButton::~QLabelButton() {

}

void QLabelButton::mouseReleaseEvent(QMouseEvent *ev) {
    emit clicked(ev);
}
