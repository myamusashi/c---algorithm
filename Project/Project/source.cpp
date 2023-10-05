#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include "login.h"

UserPass::UserPass(std::vector<std::string>* id, std::vector<std::string>* access)
    : username(id), password(access) {
}

void UserPass::ProcessRegis() {
    std::string user_input, pass_input, user_verification, pass_verification;

    std::cout << "\t\t\tHalaman registrasi user baru\n\n";
    std::cout << "Masukkans username anda: ";
    std::cin >> user_input;
    std::regex pattern("^(?=.*[A-Za-z])(?=.*\\d).+$");
    if (std::regex_match(user_input, pattern)) {
        std::cout << "Masukkan password anda: ";
        std::cin >> pass_input;
        if (std::regex_match(pass_input, pattern)) {
            std::cout << "Username dan password valid\n";
            username->push_back(user_input);
            password->push_back(pass_input);
            
            if (true) {

            } else {
                std::cout << "Salah";
            }
        } else
            std::cout << "Salah";
    } else {
        std::cout << "Salah";
    }
}


int main(int argc, const char** argv) {
    std::vector<std::string> id;
    std::vector<std::string> access;

    UserPass userpass(&id, &access);
    userpass.ProcessRegis();

    return 0;
}