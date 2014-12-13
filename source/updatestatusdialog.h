#ifndef UPDATESTATUSDIALOG_H
#define UPDATESTATUSDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class UpdateStatusDialog;
}

class UpdateStatusDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateStatusDialog(QWidget *parent = 0);
    ~UpdateStatusDialog();
    QString GetStatus();
    void setName(QString name);

private:
    Ui::UpdateStatusDialog *ui;
};

#endif // UPDATESTATUSDIALOG_H
