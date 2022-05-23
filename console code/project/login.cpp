#include "register.cpp"
int ID;
string password, name;
bool is_login;
void login_ID(){
    ID_format();
    cin >> ID;
    if(!is_ID_valid(ID)){
        login_ID();
        return;
    }
    if(!all_users.count(ID)){
        separated_line(" This ID does not exist! ");
        login_ID();
        return;
    }
    password = all_users[ID].userPassword;
    name = all_users[ID].userName;
}

void login_password(){
    static int trial_cnt = 3;
    password_format();
    string tmp = hidden_password();
    if(trial_cnt == 1){
        separated_line(" Failed to login! ");
        return;
    }
    if(!is_password_valid(password)){
        login_password();
        return;
    }
    if(tmp != password){
        separated_line(" This ID password is wrong! ");
        trial_cnt --;
        login_password();
        return;
    }
    is_login = true;
}

void login(){
    is_login = false;
    login_ID();
    login_password();
    if(is_login){
        separated_line(" Successful login!, Welcome (" + name + ") ");
    }
}