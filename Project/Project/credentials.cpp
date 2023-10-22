#include <iostream>
#include <conio.h>
#include <regex>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "credentials.h"

UserPass::UserPass(std::vector<std::string>* id, std::vector<std::string>* access)
    : username(id), password(access) {
}

// Fungsi untuk mendapatkan password dengan input tersembunyi di Windows
std::string getpass(const char* prompt) {
    std::string password;
    char ch;
    std::cout << prompt;

    while (1) {
        ch = _getch(); // Membaca karakter tanpa menampilkannya
        if (ch == 13) { // 13 adalah kode ASCII untuk tombol Enter
            std::cout << std::endl;
            break;
        }
        else if (ch == 8) { // 8 adalah kode ASCII untuk tombol Backspace
            if (!password.empty()) {
                std::cout << "\b \b"; // Menghapus karakter terakhir dari tampilan
                password.pop_back(); // Menghapus karakter terakhir dari password
            }
        }
        else {
            std::cout << '*'; // Menampilkan karakter '*' sebagai pengganti
            password.push_back(ch); // Menambahkan karakter ke password
        }
    }
    return password;
}

const int UserPass::ProcessRegister() {
    std::string back_auth;
    char back;
    
    do {
        std::cout << "\033[2J\033[1;1H";
        std::cout << "\t\t\tHalaman registrasi user baru\n";
        std::string user_input; std::cout << "Masukkan username anda: ";
        std::cin >> user_input;
        
        std::regex userRegex("^(?=.*[A-Za-z].*\\d)[A-Za-z\\d]{8,}$"); // Minimal 8 karakter dengan 1 angka
        bool user_valid = std::regex_match(user_input, userRegex);
        if (user_valid) {
            std::string pass_input = getpass("Masukkan password anda: ");

            std::regex passRegex("^(?=.*[A-Za-z].*\\d)[A-Za-z\\d]{8,}$"); // Minimal 8 karakter dengan 1 huruf besar dan 1 angka
            if (std::regex_match(pass_input, passRegex)) {
                std::cout << "Username dan password valid, akun telah terdaftar.\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));

                username->push_back(user_input);
                password->push_back(pass_input);

                do {
                    std::cout << "\033[2J\033[1;1H";
                    std::cout << "Login ke akun anda\n";
                    std::string user_verification; std::cout << "Username anda: ";
                    std::cin >> user_verification;
                    std::string pass_verification = getpass("Password anda: ");

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
                        std::cout << "Verifikasi berhasil." << std::endl;
                        std::cout << "Masuk program..." << std::endl;
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        break;
                    }
                    else {
                        std::cout << "\033[2J\033[1;1H";
                        std::cout << "Verifikasi gagal, username atau password tidak cocok." << std::endl;
                        std::this_thread::sleep_for(std::chrono::seconds(2));
                    }
                    std::cout << "Login kembali? (y/n)";
                    std::cin >> back_auth;
                    if (back_auth == "n" || back_auth == "N") {
                        exit(66);
                    }
                } while (back_auth == "y" || back_auth == "Y");
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
    std::string back;

    do {
        std::cout << "\033[2J\033[1;1H";
        std::cout << "Masuk ke halaman login...\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::string loginUser; std::cout << "Login username: ";
        std::cin >> loginUser;
        std::string loginPass = getpass("Login password: ");

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