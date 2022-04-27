#include <bits/stdc++.h>
#include "register.cpp"
using namespace std;
int choose;

void fill_space(string paragraph, int paragraph_width){
    int width = 180;
    cout << string((width/2) - (paragraph_width/2),' ')<< paragraph;
}

void show_menu(){
    // store all paragraphs in a vector
    vector<string>menu_choices(5);
    menu_choices[0] = "Choose what you want from this menu";
    menu_choices[1] = "1- Register";
    menu_choices[2] = "2- Login |";
    menu_choices[3] = "3- Change password";
    menu_choices[4] = "4- Exit";
    // get max width of this paragraphs
    int max_paragraph_width = 0;
    for(auto& val : menu_choices){
        max_paragraph_width = max(max_paragraph_width, (int)val.size());
    }
    // center welcome paragraph
    fill_space("Welcome",-(max_paragraph_width/2) + 20);
    cout << '\n';
    // print the first (-) line in the shape
    fill_space(string(max_paragraph_width + 5,'-'),max_paragraph_width-1);
    cout << '\n';
    // print shape content and its sides
    for(auto& val : menu_choices){
        fill_space("|  " + val,max_paragraph_width);
        cout << string(max_paragraph_width - (int)val.size(),' ') << " |\n";
    }
    // print the last (-) line in the shape
    fill_space(string(max_paragraph_width + 5,'-'),max_paragraph_width-1);
    cout << '\n';
}

void take_choice(){
    cout << "Enter your choice: ";
    cin >> choose;
    if(choose < 0 || choose > 4){
        separated_line(" Enter correct choice ");
        take_choice();
        return;
    }
    switch (choose) {
        case 1:
            register_menu();
            break;
        case 2:
            if(!login_menu()){
                show_menu();
                take_choice();
                return;
            }
            break;
        case 3:
            change_password_menu();
            break;
        case 4:
            return;
    }
}

int main(){
    load_file_information();
    show_menu();
    take_choice();
    save_information();
}
