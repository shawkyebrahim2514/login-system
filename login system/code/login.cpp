#include <bits/stdc++.h>
#include "user_information.cpp"

using namespace std;
string ID;
int trials = 3;
bool correct_user = false;
void inquire_id(){
    separated_line("");
    cout << "Enter your ID: ";
    cin >> ID;
    if(!users_list.count(ID)){
        separated_line(" Please enter correct user ID ");
        inquire_id();
        return;
    }
}
void inquire_password(){
    separated_line("");
    if(!trials){
        separated_line(" Failed login, try again ");
        trials = 3;
        return;
    }
    string pass = "";
    hidden_password(pass, "Enter your password: ");
    if(users_list[ID].password != pass){
        separated_line(" You entered wrong password ");
        trials--;
        inquire_password();
        return;
    }
    correct_user = true;
}

bool login_menu(){
    inquire_id();
    inquire_password();
    if(correct_user){
        separated_line(" Successful login, welcome " + users_list[ID].name + ' ');
        return 1;
    }else{
        return 0;
    }
}