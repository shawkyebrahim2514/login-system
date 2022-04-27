cmake_minimum_required(VERSION 3.20)
project(code)

set(CMAKE_CXX_STANDARD 17)


add_executable(user user_information.cpp)
add_executable(login login.cpp)
add_executable(register register.cpp)
add_executable(change_password  change_password.cpp)
add_executable(menu main_menu.cpp)
add_executable(validation validation.cpp)
