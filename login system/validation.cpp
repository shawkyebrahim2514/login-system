#include <bits/stdc++.h>
#include<conio.h>
using namespace std;


bool email_validation(string& s){
    string tmp = "[(a-zA-z0-9)(# ! % $ ‘ & + * – / = ? ^ _` { | } ~)]+";
    regex state(tmp + "(.)?" + tmp + "[@][a-z]+(.com)");
    return regex_match(s,state);
}

bool phone_number_validation(string &s){
    regex state("(01)[0|1|2|5][\\d]{8}");
    return regex_match(s,state);
}

bool user_name_validation(string& s){
    regex state("[a-zA-Z(_)]+");
    return regex_match(s,state);
}

bool password_validation(string& s){
    if(s.size() < 12){
        return 0;
    }
    int digits = 0, alphas = 0, symbols = 0;
    for (int i = 0; i < s.size(); ++i) {
        if(isalpha(s[i])){
            alphas ++;
        }else if(isdigit(s[i])){
            digits ++;
        }else{
            symbols ++;
        }
    }
    return digits * alphas * symbols;
}
void separated_line(string paragraph){
    // centre each paragraph with (-) in each part of this paragraph
    int width = 80;
    char symbol = '-';
    int part = (width/2) - ((int)paragraph.size()/2);
    cout << string(part,symbol) + paragraph + string(part,symbol) << '\n';
}

void email_format(){
    separated_line("");
    cout << "Email must be in the format\n";
    cout << "alphabets or digit characters followed by @ then domain name and in the end (.com)\n";
}

void phone_number_format(){
    separated_line("");
    cout << "Phone number must be in the format\n";
    cout << "(010) or (011) or (012) or (015) + (8)digits\n";
}

void user_name_format(){
    separated_line("");
    cout << "User name must be in the format\n";
    cout << "only alphabetic letters or underscore(_)\n";
}

void password_format(){
    separated_line("");
    cout << "Password must be in the format\n";
    cout << "must contain at least one alphabetic character and one digit and one symbol\n";
    cout << "the length of the password must be at least 12 letters\n";
}

void hidden_password(string& s, string paragraph){
    char c;
    cout << paragraph;
    while (true) {
        c = getch();
        if(c == 13){
            // if the user press enter, break the loop
            break;
        }else if(c == 8 && s.size()){
            // if user press backspace
            s.pop_back();
            wcout << '\b' << ' ' << '\b';
        }else if(c != 8){
            cout << '*';
            s.push_back(c);
        }
    }
    cout << '\n';
}
