#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class AddUserDialog;
}

class AddUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddUserDialog(QWidget *parent = 0);
    ~AddUserDialog();
    void UpdatePicture(QString filename);
    QString GetImageFileName();
    QString GetName();

private slots:
    void on_btn_Choose_clicked();

private:
    Ui::AddUserDialog *ui;
    QString _fileName;
};

#endif // ADDUSERDIALOG_H
