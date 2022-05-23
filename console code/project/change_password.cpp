#include "login.cpp"
void changed_password(){
    string tmp;
    password_format();
    cin >> tmp;
    if(!is_password_valid(tmp)){
        changed_password();
        return;
    }
    if(all_users[ID].previous_passwords.count(tmp)){
        separated_line(" Password was used before!, enter new one ");
        changed_password();
        return;
    }
    all_users[ID].userPassword = tmp;
    all_users[ID].previous_passwords.insert(tmp);
}

void change_user_password(){
    login();
    changed_password();
    separated_line(" Password has been changed successfully! ");
}