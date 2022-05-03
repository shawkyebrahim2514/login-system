#include <bits/stdc++.h>
#include "change_password.cpp"
using namespace std;
user new_user;
string new_ID;

void enter_id(){
    separated_line("");
    cout << "Enter your new ID: ";
    cin >> new_ID;
    if(users_list.count(new_ID)){
        separated_line(" This ID was used before ");
        enter_id();
        return;
    }
}

void enter_user_name(){
    user_name_format();
    string tmp;
    cout << "Enter your name: ";
    cin >> tmp;
    if(!user_name_validation(tmp)){
        separated_line(" Please enter correct user name format ");
        enter_user_name();
        return;
    }
    new_user.name = tmp;
}

void enter_password(){
    password_format();
    string password = "", check_password = "";
    hidden_password(password, "Enter your password: ");
    if(!password_validation(password)){
        separated_line(" Enter correct password format ");
        enter_password();
        return;
    }
    hidden_password(check_password, "Enter your password again: ");
    if(password != check_password){
        separated_line(" Please enter the same password ");
        enter_password();
        return;
    }
    new_user.password = password;
    new_user.all_passwords.insert(password);
}

void enter_email(){
    email_format();
    string tmp;
    cout << "Enter your email: ";
    cin >> tmp;
    if(emails.count(tmp)){
        separated_line(" This emails was used before! ");
        enter_email();
        return;
    }
    if(!email_validation(tmp)){
        separated_line(" Enter correct email format ");
        enter_email();
        return;
    }
    new_user.email = tmp;
}

void enter_phone_number(){
    phone_number_format();
    string tmp;
    cout << "Enter your phone number\n";
    cin >> tmp;
    if(!phone_number_validation(tmp)){
        separated_line(" Enter correct phone number format ");
        enter_phone_number();
        return;
    }
    new_user.phone_number = tmp;
}

void update_users_list(){
    users_list.insert({new_ID,new_user});
    emails.insert(new_user.email);
}

void register_menu(){
    enter_id();
    enter_user_name();
    enter_password();
    enter_email();
    enter_phone_number();
    update_users_list();
}