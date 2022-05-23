#include "loginwindow.h"
#include "mainwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
QString login_password;
bool check_hidden = true;
loginWindow::loginWindow(map<int, user>& user_info, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginWindow)
{
    ui->setupUi(this);
    login_user_map = user_info;
}

loginWindow::~loginWindow()
{
    delete ui;
}

void loginWindow::on_loginButton_clicked()
{
    int ID = stoi(ui->ID_area->text().toStdString());
    string Password = ui->password_area->text().toStdString();
    if(!login_user_map.count(ID)){
        QMessageBox::warning(this,"Wrong","please, enter correct ID");
    }else if(!login_user_map[ID].comp_user_password(Password)){
        QMessageBox::warning(this,"Wrong","Password is not correct");
    }else{
        QMessageBox::information(this,"Successfully","Successfully login");
        hide();
    }
}


void loginWindow::on_password_area_textChanged(const QString &arg1)
{
    if(check_hidden){
        QString tmp = QString(arg1.size(),'*');
        ui->password_area->setText(tmp);
    }
}


void loginWindow::on_password_area_textEdited(const QString &arg1)
{
    if(arg1.size()) login_password += arg1[arg1.size()-1];
    else login_password = "";
}


void loginWindow::on_showPasswordButton_clicked()
{
    if(check_hidden){
        QString tmp = login_password;
        check_hidden = false;
        ui->password_area->setText(tmp);
    }else{
        QString tmp = QString(login_password.size(),'*');
        check_hidden = true;
        ui->password_area->setText(tmp);
    }
}

