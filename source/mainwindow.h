#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "user.h"
#include <QString>
#include <QSqlDatabase>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void UpdateButton(User user);
    void SetUser(int userNumber);
    void UpdateAllButtons();
    void SetupDB(QString configPath, QString configFileName);
    void SaveUsersToFile(QString configPath, QString configFileName);
    int AddUserToDB(User *user);
    void UpdateUser(User user);

private slots:
    void on_pushButton_clicked(QMouseEvent *);
    void on_actionExit_triggered();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();


private:
    Ui::MainWindow *ui;
    User users[10];
    int _totalUsers;
    QSqlDatabase db;
};

#endif // MAINWINDOW_H
