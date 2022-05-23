#include "changepasswordwindow.h"
#include "mainwindow.h"
#include "ui_changepasswordwindow.h"
#include <QMessageBox>
bool isOldPass_hidden = true, isNewPass_hidden = true, is_AgainNewPass_hidden = true;
QString oldPass, newPass, againNewPass;
changePasswordWindow::changePasswordWindow(map<int, user>& user_info, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changePasswordWindow)
{
    ui->setupUi(this);
    user_map = user_info;
}

changePasswordWindow::~changePasswordWindow()
{
    delete ui;
}

void changePasswordWindow::on_pushButton_2_clicked()
{
    hide();
}


void changePasswordWindow::on_oldPass_area_textChanged(const QString &arg1)
{
    if(isOldPass_hidden){
        QString tmp = QString(arg1.size(),'*');
        ui->oldPass_area->setText(tmp);
    }
}


void changePasswordWindow::on_oldPass_area_textEdited(const QString &arg1)
{
    if(arg1.size()) oldPass += arg1[arg1.size()-1];
    else oldPass = "";
}


void changePasswordWindow::on_showOldPass_clicked()
{
    if(isOldPass_hidden){
        QString tmp = oldPass;
        isOldPass_hidden = false;
        ui->oldPass_area->setText(tmp);
    }else{
        QString tmp = QString(oldPass.size(),'*');
        isOldPass_hidden = true;
        ui->oldPass_area->setText(tmp);
    }
}


void changePasswordWindow::on_newPass_area_textChanged(const QString &arg1)
{
    if(isNewPass_hidden){
        QString tmp = QString(arg1.size(),'*');
        ui->newPass_area->setText(tmp);
    }
}


void changePasswordWindow::on_newPass_area_textEdited(const QString &arg1)
{
    if(arg1.size()) newPass += arg1[arg1.size()-1];
    else newPass = "";
}


void changePasswordWindow::on_showNewPass_clicked()
{
    if(isNewPass_hidden){
        QString tmp = newPass;
        isNewPass_hidden = false;
        ui->newPass_area->setText(tmp);
    }else{
        QString tmp = QString(newPass.size(),'*');
        isNewPass_hidden = true;
        ui->newPass_area->setText(tmp);
    }
}


void changePasswordWindow::on_againNewPass_area_textChanged(const QString &arg1)
{
    if(is_AgainNewPass_hidden){
        QString tmp = QString(arg1.size(),'*');
        ui->againNewPass_area->setText(tmp);
    }
}


void changePasswordWindow::on_againNewPass_area_textEdited(const QString &arg1)
{
    if(arg1.size()) againNewPass += arg1[arg1.size()-1];
    else againNewPass = "";
}


void changePasswordWindow::on_showAgainNewPass_clicked()
{
    if(is_AgainNewPass_hidden){
        QString tmp = againNewPass;
        is_AgainNewPass_hidden = false;
        ui->againNewPass_area->setText(tmp);
    }else{
        QString tmp = QString(againNewPass.size(),'*');
        is_AgainNewPass_hidden = true;
        ui->againNewPass_area->setText(tmp);
    }
}


void changePasswordWindow::on_doneButton_clicked()
{
    int ID = stoi(ui->IDarea->text().toStdString());
    string s_oldPass = oldPass.toStdString();
    if(!user_map.count(ID)){
        QMessageBox::warning(this,"Wrong","Enter correct ID!");
    }else if(!user_map[ID].comp_user_password(s_oldPass)){
        QMessageBox::warning(this, "Wrong", "Wrong password!");
    }else{
        QMessageBox::warning(this,"successfully", "Hello " + QString::fromStdString(user_map[ID].get_name()) + ", your profile has been updated.");
        string s_newPass = newPass.toStdString();
        user_map[ID].change_pass(s_newPass);
        hide();
    }
}

