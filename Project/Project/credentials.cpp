#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "credentials.h"

UserPass::UserPass(std::vector<std::string>* id, std::vector<std::string>* access)
    : username(id), password(access) {
}

void UserPass::ProcessRegister() {
    std::string user_input, pass_input, user_verification, pass_verification;
    char back;

    do {
        std::cout << "\033[2J\033[1;1H";
        std::cout << "\t\t\tHalaman registrasi user baru\n";
        std::cout << "Masukkan username anda: ";
        std::cin >> user_input;
        std::regex userRegex("^(?=.*[A-Za-z].*\\d)[A-Za-z\\d]{8,}$"); // Minimal 8 karakter dengan 1 angka
        bool user_valid = std::regex_match(user_input, userRegex);
        if (user_valid) {
            std::cout << "Masukkan password anda: ";
            std::cin >> pass_input;

            std::regex passRegex("^(?=.*[A-Za-z].*\\d)[A-Za-z\\d]{8,}$"); // Minimal 8 karakter dengan 1 huruf besar dan 1 angka
            if (std::regex_match(pass_input, passRegex)) {
                std::cout << "Username dan password valid\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                std::cout << "\033[2J\033[1;1H";
                username->push_back(user_input);
                password->push_back(pass_input);

                std::cout << "Login ke akun anda\n";
                std::cout << "Username anda: ";
                std::cin >> user_verification;
                std::cout << "Password anda: ";
                std::cin >> pass_verification;

                bool isVerified = false;
                std::cout << "verifikasi account...\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                for (size_t id = 0; id < username->size(); ++id) {
                    for (size_t access = 0; access < password->size(); access++) {
                        if ((*username)[id] == user_verification && (*password)[access] == pass_verification) {
                            isVerified = true;
                            break;
                        }
                    }
                }

                if (isVerified) {
                    std::cout << "\033[2J\033[1;1H";
                    std::cout << "Verifikasi berhasil, akun telah terdaftar." << std::endl;
                    std::cout << "Masuk program..." << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    break;
                }
                else {
                    std::cout << "\033[2J\033[1;1H";
                    std::cout << "Verifikasi gagal, username atau password tidak cocok." << std::endl;
                }
            }
            else {
                std::cout << "Password invalid, minimal 8 karakter dan 1 huruf besar dan 1 angka" << std::endl;
            }
        }
        else {
            std::cout << "Username invalid, minimal 8 karakter dan 1 angka" << std::endl;
        }
        std::cout << "Ingin Registrasi kembali? (y/n)? ";
        std::cin >> back;
    } while (back == 'y' || back == 'Y');
}

void UserPass::LoginProgram() {
    std::string loginUser, loginPass, back;

    do {
        std::cout << "\033[2J\033[1;1H";
        std::cout << "Masuk ke halaman login...\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Login username: ";
        std::cin >> loginUser;
        std::cout << "Login password: ";
        std::cin >> loginPass;

        bool isVerified = false;
        for (size_t id = 0; id < username->size(); ++id) {
            if ((*username)[id] == loginUser && (*password)[id] == loginPass) {
                isVerified = true;
                break;
            }
        }
        if (isVerified) {
            std::cout << "Verifikasi berhasil\n";
            std::cout << "Akan masuk ke dalam program...";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }
        else {
            std::cout << "Verifikasi gagal, coba lagi\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::cout << "Masuk ke program? (y/n)? ";
        std::cin >> back;
    } while (back == "y" || back == "Y" || back == "ya" || back == "Ya" || back == "yes");
}