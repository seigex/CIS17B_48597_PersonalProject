#include "user.h"
#include <QDir>

User::User()
{
    this->_enabled = false;
    this->_name = QString("");
    this->_status = STATUS_OFF;
    this->_statusText = QString("");

    QDir qDir;
    this->_imageName = "placeholder.png";
}

void User::setID(int id) {
    this->_id = id;
}

void User::setStatus(int status) {
    this->_status = status;
}

void User::setStatusText(QString statusText) {
    this->_statusText = statusText;
}

void User::setName(QString name) {
    this->_name = name;
}

void User::setEnabled(bool enabled) {
    this->_enabled = enabled;
}

void User::setButton(QLabelButton *pushButton) {
    this->_assignedButton = pushButton;
}

void User::setImageName(QString path) {
    this->_imageName = path;
}

//getters
int User::getStatus() {
    return this->_status;
}

QString User::getStatusText() {
    return this->_statusText;
}

QString User::getName() {
    return this->_name;
}

int User::getID() {
    return this->_id;
}

bool User::getEnabled() {
    return this->_enabled;
}

QLabelButton *User::getButton() {
    return this->_assignedButton;
}

QString User::getImageName() {
    return this->_imageName;
}

QString User::getImageFullPath() {
    QDir qDir;
    return QString(qDir.absolutePath()).append("/PROFILEPICS/").append(this->_imageName);
}

void User::clear() {
    this->_enabled = false;
    this->_name = "";
    this->_status = STATUS_OFF;
    this->_statusText = "";
    QDir qDir;
    this->_imageName = "placeholder.png";
}
