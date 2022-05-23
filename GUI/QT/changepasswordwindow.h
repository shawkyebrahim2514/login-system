#ifndef CHANGEPASSWORDWINDOW_H
#define CHANGEPASSWORDWINDOW_H

#include <QDialog>
#include <bits/stdc++.h>
using namespace std;
class user;

namespace Ui {
class changePasswordWindow;
}

class changePasswordWindow : public QDialog
{
    Q_OBJECT

public:
    map<int, user> user_map;
    explicit changePasswordWindow(map<int, user>& user_info, QWidget *parent = nullptr);
    ~changePasswordWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_oldPass_area_textChanged(const QString &arg1);

    void on_oldPass_area_textEdited(const QString &arg1);

    void on_showOldPass_clicked();

    void on_newPass_area_textChanged(const QString &arg1);

    void on_newPass_area_textEdited(const QString &arg1);

    void on_showNewPass_clicked();

    void on_againNewPass_area_textChanged(const QString &arg1);

    void on_againNewPass_area_textEdited(const QString &arg1);

    void on_showAgainNewPass_clicked();

    void on_doneButton_clicked();

private:
    Ui::changePasswordWindow *ui;
};

bool is_password_valid(string& password);
bool is_ID_valid(string& ID);

#endif // CHANGEPASSWORDWINDOW_H
