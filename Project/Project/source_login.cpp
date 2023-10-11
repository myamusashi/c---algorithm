#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "data_login.h"

UserPass::UserPass(std::vector<std::string>* id, std::vector<std::string>* access)
    : username(id), password(access) {
}

void UserPass::ProcessRegister() {
    std::string user_input, pass_input, user_verification, pass_verification;
    char back;

    do {
        system("cls");
        std::cout << "\t\t\tHalaman registrasi user baru\n\n";
        std::cout << "Masukkan username anda: ";
        std::cin >> user_input;
        std::regex userRegex("^(?=.*\d).{8,}$"); // Minimal 8 karakter dengan 1 huruf angka
        std::regex passRegex("^(?=.*[A-Z])(?=.*\\d).{8,}$"); // Minimal 8 karakter dengan 1 huruf besar dan 1 angka
        if (std::regex_match(user_input, userRegex)) {
            std::cout << "Masukkan password anda: ";
            std::cin >> pass_input;
            if (std::regex_match(pass_input, passRegex)) {
                std::cout << "Username dan password valid\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                username->push_back(user_input);
                password->push_back(pass_input);
                system("cls");
                std::cout << "\t\t\tLogin ke akun anda\n\n";
                std::cout << "Username anda: ";
                std::cin >> user_verification;
                std::cout << "Password anda: ";
                std::cin >> pass_verification;

                // Periksa apakah ada username dan password yang cocok dalam vektor
                bool isVerified = false;
                for (size_t id = 0; id < username->size(); ++id) {
                    if ((*username)[id] == user_verification && (*password)[id] == pass_verification) {
                        isVerified = true;
                        break;
                    }
                }

                if (isVerified) {
                    std::cout << "Verifikasi berhasil, akun telah terdaftar.\n";
                    std::cout << "Masuk program...";
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                    break;
                }
                else {
                    std::cout << "Verifikasi gagal, username atau password tidak cocok.\n";
                    std::cout << "Keluar dari halaman...";
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                }
            }
            else {
                std::cout << "Password invalid, inimal 8 karakter dan 1 huruf besar dan 1 angka";
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
        }
        else {
            std::cout << "Username invalid, minimal 8 karakter dan 1 angka";
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }

        std::cout << "\nIngin Registrasi kembali? (y/n)? ";
        std::cin >> back;
    } while (back == 'y' || back == 'Y');
}

void UserPass::LoginProgram() {
    std::string loginUser, loginPass, back;

    do {
        system("cls");
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