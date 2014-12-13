#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DECLARATIONS.h"
#include <QDebug>
#include <QDir>
#include <QPushButton>
#include <QMouseEvent>
#include "updatestatusdialog.h"
#include "adduserdialog.h"
#include <QMessageBox>
#include <QPixmap>
#include <QProcess>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDir qDir;
    QString currentPath = qDir.absolutePath();
    /*************/
    /* TEMP DATA */
    /*************/

    ui->pushButton1->setProperty("itemnumber", 0);
    connect(ui->pushButton1, SIGNAL(clicked(QMouseEvent *)), this, SLOT(on_pushButton_clicked(QMouseEvent *)));
    users[0].setButton(ui->pushButton1);

    ui->pushButton2->setProperty("itemnumber", 1);
    connect(ui->pushButton2, SIGNAL(clicked(QMouseEvent *)), this, SLOT(on_pushButton_clicked(QMouseEvent *)));
    users[1].setButton(ui->pushButton2);

    ui->pushButton3->setProperty("itemnumber", 2);
    connect(ui->pushButton3, SIGNAL(clicked(QMouseEvent *)),this, SLOT(on_pushButton_clicked(QMouseEvent *)));
    users[2].setButton(ui->pushButton3);

    ui->pushButton4->setProperty("itemnumber", 3);
    connect(ui->pushButton4, SIGNAL(clicked(QMouseEvent *)), this, SLOT(on_pushButton_clicked(QMouseEvent *)));
    users[3].setButton(ui->pushButton4);

    ui->pushButton5->setProperty("itemnumber", 4);
    connect(ui->pushButton5, SIGNAL(clicked(QMouseEvent *)), this, SLOT(on_pushButton_clicked(QMouseEvent *)));
    users[4].setButton(ui->pushButton5);

    ui->pushButton6->setProperty("itemnumber", 5);
    connect(ui->pushButton6, SIGNAL(clicked(QMouseEvent *)), this, SLOT(on_pushButton_clicked(QMouseEvent *)));
    users[5].setButton(ui->pushButton6);

    ui->pushButton7->setProperty("itemnumber", 6);
    connect(ui->pushButton7, SIGNAL(clicked(QMouseEvent *)), this, SLOT(on_pushButton_clicked(QMouseEvent *)));
    users[6].setButton(ui->pushButton7);

    ui->pushButton8->setProperty("itemnumber", 7);
    connect(ui->pushButton8, SIGNAL(clicked(QMouseEvent *)), this, SLOT(on_pushButton_clicked(QMouseEvent *)));
    users[7].setButton(ui->pushButton8);

    ui->pushButton9->setProperty("itemnumber", 8);
    connect(ui->pushButton9, SIGNAL(clicked(QMouseEvent *)), this, SLOT(on_pushButton_clicked(QMouseEvent *)));
    users[8].setButton(ui->pushButton9);

    ui->pushButton10->setProperty("itemnumber", 9);
    connect(ui->pushButton10, SIGNAL(clicked(QMouseEvent *)), this, SLOT(on_pushButton_clicked(QMouseEvent *)));
    users[9].setButton(ui->pushButton10);

    for (int i = 0; i < 10; i++) {
        users[i].clear();
    }

    SetupDB(qDir.absolutePath() + "/CONFIG/", "sqlconfig.cfg");
    UpdateAllButtons();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked(QMouseEvent *event)
{
    QLabelButton *button = (QLabelButton *)this->sender();
    qDebug() << "Button: " << button->property("itemnumber").toInt() << endl;
    int userNumber = button->property("itemnumber").toInt();

    if (event->button() == Qt::LeftButton) {
        switch (users[userNumber].getStatus()) {
        case STATUS_IN:
          users[userNumber].setStatus(STATUS_OUT);
          break;
        case STATUS_OUT:
          users[userNumber].setStatus(STATUS_OFF);
          break;
        case STATUS_OFF:
          users[userNumber].setStatus(STATUS_IN);
          break;
        default:
            users[userNumber].setStatus(STATUS_OFF);
            break;

        }
    } else if (event->button() == Qt::RightButton) {
        UpdateStatusDialog updateStatusDialog;
        updateStatusDialog.setName(users[userNumber].getName());
        //updateStatusDialog.setModal(true);
        if (updateStatusDialog.exec() == QDialog::Accepted) {
            QString status = updateStatusDialog.GetStatus();
            users[userNumber].setStatusText(status);
            UpdateUser(users[userNumber]);
        }
    }

    QDir qDir;
    UpdateUser(users[userNumber]);
    UpdateButton(users[userNumber]);

}

void MainWindow::UpdateButton(User user) {    
    if (user.getEnabled()) {
        qDebug() << user.getImageFullPath() << endl;

        user.getButton()->setText("<table style='color:white;font-size:20px;font-weight:bold;'> \
                                  <tr><td rowspan=3><img src='" + user.getImageFullPath() + "' /><td>" + user.getName() + "</td></tr> \
                                  <tr><td>&nbsp;</td></tr> \
                                  <tr><td style='margin-left:10px;'>" + user.getStatusText() + "</td></tr> \
                                  </table>");
        if (user.getStatus() == STATUS_IN)
            user.getButton()->setStyleSheet("background-color: green;");
        else if (user.getStatus() == STATUS_OUT)
            user.getButton()->setStyleSheet("background-color: red;");
        else if (user.getStatus() == STATUS_OFF)
            user.getButton()->setStyleSheet("background-color: gray;");
        user.getButton()->setEnabled(true);
    }
    else {
        user.getButton()->setEnabled(false);
        user.getButton()->setStyleSheet("background-color: none;");
    }
}

void MainWindow::UpdateAllButtons() {
    for (int i = 0; i < 10; i++) {
        UpdateButton(users[i]);
    }
}

void MainWindow::SetupDB(QString configPath, QString configFileName) {

    QDir qDir;

    QFile configFile(configPath + configFileName);
    QStringList sqlValues;

    if (configFile.exists()) {
        if (!configFile.open(QIODevice::ReadOnly)) {
            qDebug() << "Cannot open file: " << qPrintable(configFile.errorString()) << endl;
        } else {
            QTextStream in(&configFile);
            if (!in.atEnd()) {
                QString inLine = in.readLine();
                sqlValues = inLine.split('|');
            }
            configFile.close();

            if (sqlValues.count() == 4) {

                QString host = sqlValues.at(0);
                QString user = sqlValues.at(1);
                QString password = sqlValues.at(2);
                QString dbname = sqlValues.at(3);

                this->db = QSqlDatabase::addDatabase("QMYSQL");
                db.setHostName(host);
                db.setDatabaseName(dbname);
                db.setUserName(user);
                db.setPassword(password);

                if (db.open()) {
                    QSqlQuery query;
                    int count = 0;
                    query.exec("SELECT * FROM outboard order by id");
                    while (query.next()) {
                        users[count].setID(query.value(0).toInt());
                        users[count].setName(query.value(1).toString());
                        users[count].setEnabled(query.value(2).toInt() == 1 ? true : false);
                        users[count].setStatus(query.value(3).toInt());
                        users[count].setImageName(query.value(4).toString());
                        users[count].setStatusText(query.value(5).toString());
                        count++;
                    }
                    db.close();
                    this->_totalUsers = count - 1;
                    qDebug() << "Number Of Users Loaded: " << count << endl;
                }
            }
        }
    }
}

int MainWindow::AddUserToDB(User *user) {

    try {
        if (db.open()) {
            qDebug() << "AddUserToDB: Database opened!" << endl;
            QSqlQuery query;
            query.prepare("INSERT INTO outboard (name, enabled, status, imagename, statustext) values (:name,:enabled,:status, :imagename, :statustext)");
            query.bindValue(":name",user->getName());
            query.bindValue(":enabled",user->getEnabled() ? 1 : 0);
            query.bindValue(":status",user->getStatus());
            query.bindValue(":imagename",user->getImageName());
            query.bindValue(":statustext",user->getStatusText());

            int id;

            if (query.exec()) {
              qDebug() << "AddUserToDB: User added!" << endl;

              query.exec("SELECT LAST_INSERT_ID()");
              if (query.next()) {
              id = query.record().value(0).toInt();
              user->setID(id);
              qDebug() << "ID Number Inserted: " << id << endl;
              }
              db.close();
              return id;
            } else
                qDebug() << "AddUserToDB SQL Query Failed: " << query.lastError().databaseText();
        }
        else
        {
            qDebug() << "AddUserToDB: Unable to open database!" << endl;
        }
    } catch (std::exception exc) {
        qDebug() << "AddUserToDB: Unable to add user: " << exc.what() << endl;
    }
    return -1;
}

void MainWindow::UpdateUser(User user) {

    try {
        if (db.open()) {
            qDebug() << "UpdateUser: Database opened!" << endl;
            QSqlQuery query;
            query.prepare("UPDATE outboard SET name = :name, enabled = :enabled, status = :status, imagename = :imagename, statustext = :statustext where id = :id");
            query.bindValue(":name",user.getName());
            query.bindValue(":enabled",user.getEnabled() ? 1 : 0);
            query.bindValue(":status",user.getStatus());
            query.bindValue(":imagename",user.getImageName());
            query.bindValue(":statustext",user.getStatusText());
            query.bindValue(":id",user.getID());

            if (query.exec()) {
              qDebug() << "UpdateUser: User updated!" << " " << endl;
            }
            else
                qDebug() << "AddUserToDB SQL Query Failed: " << query.lastError().databaseText();

            db.close();
        }
        else
        {
            qDebug() << "UpdateUser: Unable to open database!" << endl;
        }
    } catch (std::exception exc) {
        qDebug() << "UpdateUser: Unable to update user: " << exc.what() << endl;
    }
}

void MainWindow::on_actionExit_triggered() {
  QApplication::quit();
}


void MainWindow::on_pushButton_clicked()
{
    if (this->_totalUsers >= 10) {
        QMessageBox::warning(this, tr("Too Many Users"), tr("Delete one before you can add more."));
    } else {
        AddUserDialog addUserDialog;
        if (addUserDialog.exec() == QDialog::Accepted) {
            QString name = addUserDialog.GetName();
            QString picturePath = addUserDialog.GetImageFileName();
            if (name.isEmpty() || picturePath.isEmpty())
                QMessageBox::warning(this, tr("Error"), tr("Fields weren't completed."));
            else {
                qDebug() << picturePath.length() << ":" << picturePath.lastIndexOf('/') << endl;
                QString imageFileName = picturePath.right(picturePath.length()-picturePath.lastIndexOf('/')-1);
                qDebug() << imageFileName << endl;
                QDir qDir;
                QString toPath = QString(qDir.absolutePath()).append("/PROFILEPICS/").append(imageFileName);
                QPixmap qPixMap;
                qPixMap.load(picturePath);
                qPixMap.scaled(QSize(84, 97)).toImage().save(toPath);
                this->_totalUsers++;
                this->users[this->_totalUsers].setName(name);
                this->users[this->_totalUsers].setImageName(imageFileName);
                this->users[this->_totalUsers].setEnabled(true);
                this->users[this->_totalUsers].setStatus(2);
                this->AddUserToDB(&this->users[this->_totalUsers]);
                this->UpdateButton(this->users[this->_totalUsers]);
            }

            //QString status = AddUserDialog.getName();
            //users[userNumber].setStatusText(status);
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QDir qDir;
    QString file = qDir.absolutePath().append("/config/notepad2.exe").append(" sqlconfig.cfg");
    QProcess process;
    qDebug() << "Opening: " << file << endl;
    process.startDetached(file);
}
