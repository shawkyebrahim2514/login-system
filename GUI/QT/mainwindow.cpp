#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "loginwindow.h"
#include "registerwindow.h"
#include "changepasswordwindow.h"
#include <QMessageBox>
#include <bits/stdc++.h>
using namespace std;
//------------------------------------------------------------
string database_name = "database.txt";
map<int, user>all_users;
set<string> all_emails;
//------------------------------------------------------------
void encrypt_and_decrypt(string& password,string type){
    int val = 15;
    if(type == "decrypt"){
        val *= -1;
    }
    for(auto& i : password){
        i += val;
    }
}
//------------------load data --------------------------------
void load_userInfo(){
    fstream file(database_name, ios::in);
    string userInfo_line, userPasswords_line, tmp;
    while (!file.eof() && file.peek() != ifstream::traits_type::eof()){
        // take user information ID, Password, Name, Email, Phone number
        vector<string> userInfo_arr;
        getline(file, userInfo_line);
        istringstream  sep_content_line(userInfo_line);
        while (sep_content_line >> tmp){
            userInfo_arr.push_back(tmp);
        }
        encrypt_and_decrypt(userInfo_arr[1],"decrypt");

        // take user passwords
        set<string> encrypted_passwords, all_passwords;
        getline(file, userPasswords_line);
        istringstream sep_passwords_line(userPasswords_line);
        while (sep_passwords_line >> tmp){
            encrypted_passwords.insert(tmp);
        }
        for(auto& val : encrypted_passwords){
            string tmp = val;
            encrypt_and_decrypt(tmp,"decrypt");
            all_passwords.insert(val);
        }

        // make user info as a struct then push it to the all user map
        user new_user;
        new_user.fill_user_info(userInfo_arr, all_passwords);
        all_users[stoi(userInfo_arr[0])] = new_user;

        // add user email to the all emails set
        all_emails.insert(userInfo_arr[3]);
    }

    file.close();
}
//-------------------------------------------------------------------
void save_userInfo(){
    fstream file(database_name, ios::out);
    int newLine_cnt = 1;
    int map_size = all_users.size();
    for(auto item : all_users){
        vector<string> all_info = item.second.get_all_info();
        encrypt_and_decrypt(all_info[1],"encrypt");
        set<string> pre_passwords = item.second.get_all_pre_passwords();
        for(auto val : all_info){
            file << val << ' ';
        }
        file << '\n';
        for(auto val : pre_passwords){
            encrypt_and_decrypt(val,"encrypt");
            file << val << ' ';
        }
        if(newLine_cnt == map_size){
            continue;
        }
        newLine_cnt++;
        file << '\n';
    }
    file.close();
}
//-------------------------------------------------------------------
bool is_ID_valid(string& ID){
    int ID_length = 5;
    bool check = true;
    if(ID.size() != ID_length){
        check = false;
    }
    return check;
}

bool is_password_valid(string& password){
    bool symbol = false, alpha = false, digit = false;
    for(char i : password){
        if(isalpha(i)){
            alpha = true;
        }else if(isdigit(i)){
            digit = true;
        }else{
            symbol = true;
        }
    }
    return symbol & alpha & digit;
}

bool is_name_valid(string& name){
    regex statement("(_?)[a-zA-Z]+");
    return regex_match(name, statement);;
}

bool is_email_valid(string& email){
    string sub_statement = "[0-9a-zA-Z._]+";
    regex statement(sub_statement + "[@]" + sub_statement + "(.com)");
    return regex_match(email,statement);
}

bool is_phoneNumber_valid(string& phoneNumber){
    regex statement("((010)|(011)|(012)|(015))[0-9]{8}");
    bool check = regex_match(phoneNumber,statement);
    return regex_match(phoneNumber,statement);
}
//-------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    load_userInfo();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_registerButton_clicked()
{
    registerWindow screen(all_users, all_emails);
    screen.setModal(true);
    screen.exec();
    all_users = screen.reg_user_map;
    all_emails = screen.reg_user_emails;
}


void MainWindow::on_loginButton_clicked()
{
    loginWindow screen(all_users);
    screen.setModal(true);
    screen.exec();

}


void MainWindow::on_changePasswordButton_clicked()
{
    changePasswordWindow screen(all_users);
    screen.setModal(true);
    screen.exec();
    all_users = screen.user_map;
}


void MainWindow::on_exitButton_clicked()
{
    save_userInfo();
    hide();
}

