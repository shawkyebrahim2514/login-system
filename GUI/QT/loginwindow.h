#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <bits/stdc++.h>
using namespace std;
class user;
namespace Ui {
class loginWindow;
}

class loginWindow : public QDialog
{
    Q_OBJECT

public:
    map<int, user> login_user_map;
    explicit loginWindow(map<int, user>& user_info, QWidget *parent = nullptr);
    ~loginWindow();

private slots:
    void on_loginButton_clicked();

    void on_password_area_textChanged(const QString &arg1);

    void on_password_area_textEdited(const QString &arg1);

    void on_showPasswordButton_clicked();

private:
    Ui::loginWindow *ui;
};

bool is_password_valid(string& password);
bool is_ID_valid(string& ID);

#endif // LOGINWINDOW_H
