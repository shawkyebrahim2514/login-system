#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QDialog>
#include <bits/stdc++.h>
using namespace std;
class user;
namespace Ui {
class registerWindow;
}

class registerWindow : public QDialog
{
    Q_OBJECT

public:
    map<int, user> reg_user_map;
    set<string> reg_user_emails;
    QString reg_password,reg_againPassword;
    explicit registerWindow(map<int, user>& user_info,set<string>& user_email,QWidget *parent = nullptr);
    ~registerWindow();

private slots:
    void on_pushButton_clicked();

    void on_passwordArea_textChanged(const QString &arg1);

    void on_passwordArea_textEdited(const QString &arg1);

    void on_showPasswordButton_clicked();

    void on_againpasswordArea_textEdited(const QString &arg1);

    void on_againpasswordArea_textChanged(const QString &arg1);

    void on_showAgainPasswordButton_clicked();

private:
    Ui::registerWindow *ui;
};

bool is_password_valid(string& password);
bool is_phoneNumber_valid(string& phoneNumber);
bool is_email_valid(string& email);
bool is_name_valid(string& name);
bool is_ID_valid(string& ID);

#endif // REGISTERWINDOW_H
