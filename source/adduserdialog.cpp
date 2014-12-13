#include "adduserdialog.h"
#include "ui_adduserdialog.h"
#include <QDir>
#include <QCloseEvent>
#include <QDebug>
#include <QFileDialog>

AddUserDialog::AddUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUserDialog)
{
    ui->setupUi(this);
    QDir qDir;
    QString defaultFile = qDir.absolutePath().append("/PROFILEPICS/placeholder.png");
    UpdatePicture(defaultFile);
}

AddUserDialog::~AddUserDialog()
{
    delete ui;    
}

void AddUserDialog::UpdatePicture(QString filename) {
    this->_fileName = filename;
    ui->label->setPixmap(QPixmap(filename).scaled(84,97));
}

QString AddUserDialog::GetName() {
    return ui->nameLineEdit->text().trimmed();
}

QString AddUserDialog::GetImageFileName() {
    return this->_fileName;
}

void AddUserDialog::on_btn_Choose_clicked()
{
    QString selfilter = tr("IMAGE (*.jpg *.jpeg *.png *.gif)");
    QString fileName = QFileDialog::getOpenFileName(
            this,
            tr("Choose Your Avatar"),
            tr(""),
            tr("IMAGE (*.jpg *.jpeg *.png *.gif)" ),
            &selfilter
    );
    UpdatePicture(fileName);
}
