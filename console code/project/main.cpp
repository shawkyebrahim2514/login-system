#include "change_password.cpp"
void mainMenu(){
    separated_line(" Hello in the System ");
    cout << "Want do you want to choice?\n";
    cout << "1- Register new user\n";
    cout << "2- Login to exist user\n";
    cout << "3- Change exist user password\n";
    cout << "4- Exit\n";
}
void take_choice(){
    int choice;
    cout << "-> Enter you choice: ";
    cin >> choice; 
    switch (choice) {
        case 1:
            reg_user();
            break;
        case 2:
            login();
            if(!is_login){
                mainMenu();
                take_choice();
            }
            break;
        case 3:
            change_user_password();
            break;
        case 4:
            break;
        default:
            separated_line(" Enter correct choice! ");
            take_choice();
    }
}
int main() {
    load_userInfo();
    mainMenu();
    take_choice();
    save_userInfo();
}
