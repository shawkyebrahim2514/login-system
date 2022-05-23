#include "registerwindow.h"
#include "mainwindow.h"
#include "ui_registerwindow.h"
#include <QMessageBox>
bool reg_check_hidden_pass = true;
bool reg_check_hidden_againPass = true;

registerWindow::registerWindow(map<int, user>& user_info,set<string>& user_email,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerWindow)
{
    ui->setupUi(this);
    reg_user_map = user_info;
    reg_user_emails = user_email;
}

registerWindow::~registerWindow()
{
    delete ui;
}

void registerWindow::on_pushButton_clicked()
{
    string Name =ui->nameArea->text().toStdString(),
            ID = ui->IDarea->text().toStdString(),
            Password = reg_password.toStdString(),
            Email = ui->emailArea->text().toStdString(),
            Phone = ui->phoneArea->text().toStdString();
    // check validation input
    bool is_user_valid = false;
    QString user_error;
    if(!is_ID_valid(ID)){
        user_error += "Please, enter corrct ID format, ( " + QString::fromStdString(ID) + " ) is wrong\n";
        is_user_valid = true;
    }
    if(!is_password_valid(Password)){
        user_error += "Please, enter correct password format, ( " + QString::fromStdString(Password) + " ) is wrong\n";;
        is_user_valid = true;
    }
    if(!is_email_valid(Email)){
        user_error += "Please, enter correct Email format, ( " + QString::fromStdString(Email) + " ) is wrong\n";
        is_user_valid = true;
    }
    if(!is_phoneNumber_valid(Phone)){
        user_error += "Please, enter correct phone number format, ( " + QString::fromStdString(Phone) + " ) is wrong\n";
        is_user_valid = true;
    }


    if(is_user_valid){
        QMessageBox::warning(this,"Error", user_error);
    }else{
        if(reg_password != reg_againPassword){
            QMessageBox::warning(this,"Wrong", "Please, enter the same password correctly\n");
        }else if(reg_user_emails.count(Email)){
            QMessageBox::warning(this,"Wrong", "this Email was taken before\n");
        }else{
            // fill new user valid information
            set<string> prePass;
            prePass.insert(Password);
            vector<string> arr_info{ID, Password, Name, Email, Phone};
            user new_user;
            new_user.fill_user_info(arr_info, prePass);
            reg_user_map[stoi(ID)] = new_user;
            reg_user_emails.insert(Email);
            QMessageBox::information(this,"Successfully", "Successfully registered\nHello, " + QString::fromStdString(reg_user_map[stoi(ID)].get_name()));
            hide();
        }
    }
}



void registerWindow::on_passwordArea_textChanged(const QString &arg1)
{
    if(reg_check_hidden_pass){
        QString tmp = QString(arg1.size(),'*');
        ui->passwordArea->setText(tmp);
    }
}


void registerWindow::on_passwordArea_textEdited(const QString &arg1)
{
    if(arg1.size()) reg_password += arg1[arg1.size()-1];
    else reg_password = "";
}


void registerWindow::on_showPasswordButton_clicked()
{
    if(reg_check_hidden_pass){
        QString tmp = reg_password;
        reg_check_hidden_pass = false;
        ui->passwordArea->setText(tmp);
    }else{
        QString tmp = QString(reg_password.size(),'*');
        reg_check_hidden_pass = true;
        ui->passwordArea->setText(tmp);
    }
}


void registerWindow::on_againpasswordArea_textEdited(const QString &arg1)
{
    if(arg1.size()) reg_againPassword += arg1[arg1.size()-1];
    else reg_againPassword = "";
}


void registerWindow::on_againpasswordArea_textChanged(const QString &arg1)
{
    if(reg_check_hidden_againPass){
        QString tmp = QString(arg1.size(),'*');
        ui->againpasswordArea->setText(tmp);
    }
}


void registerWindow::on_showAgainPasswordButton_clicked()
{
    if(reg_check_hidden_againPass){
        QString tmp = reg_againPassword;
        reg_check_hidden_againPass = false;
        ui->againpasswordArea->setText(tmp);
    }else{
        QString tmp = QString(reg_againPassword.size(),'*');
        reg_check_hidden_againPass = true;
        ui->againpasswordArea->setText(tmp);
    }
}

