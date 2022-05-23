#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <bits/stdc++.h>
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_registerButton_clicked();

    void on_loginButton_clicked();

    void on_changePasswordButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::MainWindow *ui;
};

bool is_password_valid(string& password);
bool is_phoneNumber_valid(string& phoneNumber);
bool is_email_valid(string& email);
bool is_name_valid(string& name);
bool is_ID_valid(string& ID);
class user{
    int userID;
    string userName, userPassword, userEmail, userPhoneNumber;
    set <string> previous_passwords;
public:
    void fill_user_info(vector <string>& userInfo_arr, set <string>& pre_passwords){
        userID = stoi(userInfo_arr[0]);
        userPassword = userInfo_arr[1];
        userName = userInfo_arr[2];
        userEmail = userInfo_arr[3];
        userPhoneNumber = userInfo_arr[4];
        previous_passwords = pre_passwords;
    }
    vector<string> get_all_info(){
        vector<string> tmp(5);
        tmp[0] = to_string(userID);
        tmp[1] = userPassword;
        tmp[2] = userName;
        tmp[3] = userEmail;
        tmp[4] = userPhoneNumber;
        return tmp;
    }
    set<string> get_all_pre_passwords(){
        return previous_passwords;
    }
    bool comp_user_password(string& comp_pass){
        return comp_pass == userPassword;
    }
    string get_name(){
        return userName;
    }
    void change_pass(string& newPass){
        userPassword = newPass;
    }
};

#endif // MAINWINDOW_H
