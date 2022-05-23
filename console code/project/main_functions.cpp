#include <bits/stdc++.h>
#include<conio.h>
using namespace std;

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
map<int, user>all_users;
set<string> all_emails;

bool is_ID_valid(int& ID){
    int ID_length = 5;
    bool check = true;
    string tmp = to_string(ID);
    if(tmp.size() != ID_length){
        cout << "ID should be of 5 digits only";
        check = false;
    }
    if(!check){
        cout << "Please, enter correct format\n";
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
    bool check = symbol & alpha & digit;
    if(!check){
        cout << "Please, enter correct format\n";
    }
    return check;
}

bool is_name_valid(string& name){
    regex statement("(_?)[a-zA-Z]+");
    bool check = regex_match(name, statement);
    if(!check){
        cout << "Please, enter correct format\n";
    }
    return check;
}

bool is_email_valid(string& email){
    string sub_statement = "[0-9a-zA-Z._]+";
    regex statement(sub_statement + "[@]" + sub_statement + "(.com)");
    bool check = regex_match(email,statement);
    if(!check){
        cout << "Please, enter correct format\n";
    }
    return check;
}

bool is_phoneNumber_valid(string& phoneNumber){
    regex statement("((010)|(011)|(012)|(015))[0-9]{8}");
    bool check = regex_match(phoneNumber,statement);
    if(!check){
        cout << "Please, enter correct format\n";
    }
    return check;
}

void separated_line(string paragraph){
    // centre each paragraph with (-) in each part of this paragraph
    int width = 130;
    char symbol = '-';
    int part = (width/2) - ((int)paragraph.size()/2);
    cout << string(part,symbol) + paragraph + string(part,symbol) << '\n';
}

void ID_format(){
    separated_line("");
    separated_line(" ID must be in the format: Digits only (its size should be 5) ");
    cout << "-> Enter your ID: ";
}

void password_format(){
    separated_line("");
    separated_line(" Password must be in the format ");
    cout << "must contain at least one alphabetic character and one digit and one symbol, its length must be at least 8 letters\n";
    cout << "-> Enter your password: ";
}

void name_format(){
    separated_line("");
    separated_line(" Name must be in the format: only alphabetic letters or underscore(_) at the beginning ");
    cout << "-> Enter your name: ";
}

void email_format(){
    separated_line("");
    separated_line(" Email must be in the format: (string@domainName.com) ");
    cout << "-> Enter your email: ";
}

void phoneNumber_format(){
    separated_line("");
    separated_line(" phone number must be in the format: (010) or (011) or (012) or (015) + (8)digits ");
    cout << "-> Enter your phone number: ";
}

string hidden_password(){
    char c;
    string password = "";
    while (true) {
        c = getch();
        if(c == 13){
            // if the user press enter, break the loop
            break;
        }else if(c == 8 && password.size()){
            // if user press backspace
            password.pop_back();
            wcout << '\b' << ' ' << '\b';
        }else if(c != 8){
            cout << '*';
            password.push_back(c);
        }
    }
    cout << '\n';
    return password;
}

void encrypt_and_decrypt(string& password,string type){
    int val = 15;
    if(type == "decrypt"){
        val *= -1;
    }
    for(auto& i : password){
        i += val;
    }
}

void load_userInfo(){
    fstream file(file_name, ios::in);
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

void save_userInfo(){
    fstream file(file_name, ios::out);
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