#include "updatestatusdialog.h"
#include "ui_updatestatusdialog.h"

UpdateStatusDialog::UpdateStatusDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateStatusDialog)
{
    ui->setupUi(this);
}

UpdateStatusDialog::~UpdateStatusDialog()
{
    delete ui;
}

QString UpdateStatusDialog::GetStatus() {
    return ui->statusLineEdit->text();
}

void UpdateStatusDialog::setName(QString name) {
    ui->statusNameLabel->setText(name);
}
