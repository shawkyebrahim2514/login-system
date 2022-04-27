#include <bits/stdc++.h>
#include "login.cpp"
using namespace std;

void changed_password(){
    string password = "", check_password = "";
    password_format();
    hidden_password(password, "Enter your new password: ");
    if(users_list[ID].all_passwords.count(password)){
        separated_line(" This password was taken before ");
        changed_password();
        return;
    }
    if(!password_validation(password)){
        separated_line(" Enter correct password format ");
        changed_password();
        return;
    }
    hidden_password(check_password, "Enter your new password again: ");
    if(password != check_password){
        separated_line(" please enter the same password ");
        changed_password();
        return;
    }
    users_list[ID].password = password;
    users_list[ID].all_passwords.insert(password);
}


void change_password_menu(){
    login_menu();
    changed_password();
}
