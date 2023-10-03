#include <string>
#include <vector>
#include <iostream>
#include <regex>

#ifndef LOGIN_H
#define LOGIN_H

class UserPass {
private:
    // Data saving
    std::vector<std::string> username;
    std::vector<std::string> password;

public:
    // Constructor
    UserPass(const std::vector<std::string>& user, const std::vector<std::string>& pass) : 
        username(user), password(pass) {
    }

    void getID() {
        std::string user;
        std::cout << "\t\t\tHalaman registrasi user baru\n\n";
        std::cout << "Masukkan username anda: ";
        std::cin >> user;
        username.push_back(user);
    }

    void getPass() {
        std::string pass;
        std::cout << "\nMasukkan password anda: ";
        std::cin >> pass;
        password.push_back(pass);
    }
};
#endif
