#ifndef USER_H
#define USER_H

#include "DECLARATIONS.h"
#include <QString>
#include "qlabelbutton.h"

class User
{
public:
    User();

    //setters
    void setID(int id);
    void setStatus(int status);
    void setStatusText(QString statusText);
    void setName(QString name);
    void setImageName(QString path);
    void setEnabled(bool enabled);
    void setButton(QLabelButton *pushButton);

    //getters
    int getID();
    int getStatus();
    QString getStatusText();
    QString getName();
    QString getImageFullPath();
    QString getImageName();
    QLabelButton *getButton();
    bool getEnabled();
    void clear();

private:
    int _id;
    int _status;
    bool _enabled;
    QString _statusText;
    QString _name;
    QString _imageName;
    QLabelButton *_assignedButton;
};

#endif // USER_H
