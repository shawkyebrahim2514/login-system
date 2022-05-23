#include "main_functions.cpp"
struct reg_info{
    int ID;
    string password, name, email, phoneNumber;
    vector <string> take_info(){
        vector <string> tmp(5);
        tmp[0] = to_string(ID);
        tmp[1] = password;
        tmp[2] = name;
        tmp[3] = email;
        tmp[4] = phoneNumber;
        return tmp;
    }
};
reg_info reg;
void ID_reg(){
    ID_format();
    cin >> reg.ID;
    if(!is_ID_valid(reg.ID)){
        ID_reg();
        return;
    }
    if(all_users.count(reg.ID)){
        separated_line(" ID was taken before! ");
        ID_reg();
        return;
    }
}

void password_reg(){
    password_format();
    reg.password = hidden_password();
    if(!is_password_valid(reg.password)){
        password_reg();
    }
    cout << "-> Enter your password again: ";
    string pass_again = hidden_password();
    if(pass_again != reg.password){
        separated_line(" Passwords are not the same! ");
        password_reg();
        return;
    }
}

void name_reg(){
    name_format();
    cin >> reg.name;
    if(!is_name_valid(reg.name)){
        name_reg();
    }
}

void email_reg(){
    email_format();
    cin >> reg.email;
    if(!is_email_valid(reg.email)){
        email_reg();
    }
    if(all_emails.count(reg.email)){
        separated_line(" Email was taken before! ");
        email_reg();
        return;
    }
}

void phoneNumber_reg(){
    phoneNumber_format();
    cin >> reg.phoneNumber;
    if(!is_phoneNumber_valid(reg.phoneNumber)){
        phoneNumber_reg();
    }
}

void reg_user(){
    ID_reg();
    password_reg();
    name_reg();
    email_reg();
    phoneNumber_reg();
    user new_user;
    vector<string> info{to_string(reg.ID), reg.password, reg.name, reg.email, reg.phoneNumber};
    set<string> pre_passwords;
    pre_passwords.insert(reg.password);
    new_user.fill_user_info(info, pre_passwords);
    all_users[reg.ID] = new_user;
}