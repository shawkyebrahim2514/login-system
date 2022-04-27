#include <bits/stdc++.h>
#include "validation.cpp"
using namespace std;

// cipher user password
void cipher(string& password){
    for (int i = 0; i < password.size(); ++i) {
        password[i] =  char(93 - (password[i] -'A') +'A');
    }
}

// user class that has all user details
struct user{
    string name, password, email, phone_number;
    set<string>all_passwords;
    user(string& n, string& pass, string& e, string& ph_num);
    user();
    string copy_information();
    string copy_previous_passwords();
};

user::user(string& n, string& pass, string& e, string& ph_num) {
    // fill user information in his class
    name = n;
    password = pass;
    email = e;
    phone_number = ph_num;
    all_passwords.insert(pass);
}


string user::copy_information() {
    cipher(password);
    return name + ' ' + password + ' ' + email + ' ' + phone_number + '\n';
}

user::user() {
    cout << "";
}

string user::copy_previous_passwords() {
    string tmp = "";
    for(auto val : all_passwords){
        cipher(val);
        tmp += ' ' +  val;
    }
    return tmp + '\n';
}


map<string, user>users_list; // the key is the user ID
set<string>emails;

void load_file_information(){
    // fill users information in user list map
    fstream users_information;
    users_information.open("users information.txt",ios::in);
    string line;
    while (getline(users_information, line)){
        // get each line from the file
        istringstream sep_line(line);
        vector<string>info;
        string tmp;
        // separate each string in the line and store it in vector to build a user class
        // [0] ID, [1] name, [2] password, [3] email, [4] phone number
        while (sep_line >> tmp){
            info.push_back(tmp);
        }
        // create a user class of his information
        // decipher password
        cipher(info[2]);
        user user_class(info[1],info[2],info[3],info[4]);
        // store each user information in this map
        users_list.insert({info[0],user_class});
    }
    users_information.close();
    //---------------------------------------------------------------------------------------
    // fill all emails in emails set
    fstream emails_file;
    emails_file.open("all emails.txt", ios::in);
    while (getline(emails_file,line)){
        emails.insert(line);
    }
    emails_file.close();
    //-----------------------------------------------------------------------------------------
    //fill each user passwords set with previous passwords
    fstream  previous_passwords;
    previous_passwords.open("user passwords.txt", ios::in);
    while (getline(previous_passwords,line)){
        // this tmp vector contain user ID in the first index and other indexes are user previous passwords
        vector<string>tmp;
        string word;
        istringstream sep_words(line);
        while (sep_words >> word){
            tmp.push_back(word);
        }
        // fill user id with his passwords
        for (int i = 1; i < tmp.size(); ++i) {
            cipher(tmp[i]);
            users_list[tmp[0]].all_passwords.insert(tmp[i]);
        }
    }
    previous_passwords.close();
}

void save_information(){
    // open users information, all emails and previous passwords, delete its content, and append new one
    fstream users_information,emails_file,previous_passwords;
    users_information.open("users information.txt",ios::out);
    emails_file.open("all emails.txt",ios::out);
    previous_passwords.open("user passwords.txt",ios::out);
    for(auto& val : users_list){
        // line will contain each user information
        string line ="";
        line += val.first + ' ';
        line += val.second.copy_information();
        // append each line information into the user file
        users_information << line;
        // append each user email into all emails file
        emails_file << val.second.email << '\n';
        // append user id and his previous passwords
        line = val.first + val.second.copy_previous_passwords();
        previous_passwords << line;
    }
    emails_file.close();
    users_information.close();
}