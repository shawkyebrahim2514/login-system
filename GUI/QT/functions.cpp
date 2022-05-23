#include <bits/stdc++.h>
using namespace std;
//------------------------------------------------------------
string file_name = "database.txt";
class user{
    int userID;
    string userName, userPassword, userEmail, userPhoneNumber;
    set <string> previous_passwords;
public:
    void fill_user_info(vector <string>& userInfo_arr, set <string>& pre_passwords){
        userID = stoi(userInfo_arr[0]);
        userPassword = userInfo_arr[1];
        userName = userInfo_arr[2];
        userEmail = userInfo_arr[3];
        userPhoneNumber = userInfo_arr[4];
        previous_passwords = pre_passwords;
    }
    vector<string> get_all_info(){
        vector<string> tmp(5);
        tmp[0] = to_string(userID);
        tmp[1] = userPassword;
        tmp[2] = userName;
        tmp[3] = userEmail;
        tmp[4] = userPhoneNumber;
        return tmp;
    }
    set<string> get_all_pre_passwords(){
        return previous_passwords;
    }
    friend void login_ID();
    friend void changed_password();
};
//------------------------------------------------------------