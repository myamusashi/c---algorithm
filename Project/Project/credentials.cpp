#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <ncurses.h>
#include "data_login.h"

UserPass::UserPass(std::vector<std::string>* id, std::vector<std::string>* access)
    : username(id), password(access) {
}

void UserPass::ProcessRegister() {
    initscr();
    curs_set(1);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);

    std::string pass_input, user_verification, pass_verification;
    char back;

    do {
        clear();
        refresh();
        attron(COLOR_PAIR(1));
        mvprintw(2, 2, "\t\t\tHalaman registrasi user baru");
        mvprintw(4, 2, "Masukkan username anda: ");
        refresh();
        noecho();

        std::string user_input; // store maksimal input
        int chin;
        int i = 0;
        while ((chin = getch()) != '\n') {
         if (chin == KEY_BACKSPACE || chin == 127) { // Tombol Backspace
          if (i > 0) {
            i--;
            mvaddch(4, 26 + i, ' '); // Hapus karakter dari layar
            mvaddch(4, 26 + i - 1, ' '); // Hapus karakter dari layar (untuk karakter sebelumnya)
            refresh();
          }
        } else if (chin == ' ') {
          // Tidak melakukan apa-apa saat karakter spasi dimasukkan
        } else {
          user_input[i] = chin;
          i++;
          printw("%c", chin);
          refresh();
          }
        }

        user_input[i] = '\0';
        echo();

        std::regex userRegex("^[a-zA-Z0-9_]{8,}$"); // Minimal 8 karakter dengan 1 angka
        if (std::regex_match(user_input, userRegex)) {
            mvprintw(6, 2, "Masukkan password anda: ");
            refresh();
            noecho();
            std::string pass_input; // store maksimal input
            int chin;
            int i = 0;
            while ((chin = getch()) != '\n') {
              if (chin == KEY_BACKSPACE || chin == 127) { // Tombol Backspace
                if (i > 0) {
                  i--;
                  mvaddch(6, 26 + i, ' '); // Hapus karakter dari layar
                  mvaddch(6, 26 + i - 1, ' '); // Hapus karakter dari layar (untuk karakter sebelumnya)
                  refresh();
                }
              } else if (chin == ' ') {
              // Tidak melakukan apa-apa saat karakter spasi dimasukkan
              } else {
                pass_input[i] = chin;
                i++;
                printw("%c", chin);
                refresh();
              }
            }
            pass_input[i] = '\0';
            echo();

            std::regex passRegex("^(?=.*[A-Z])(?=.*\\d).{8,}$"); // Minimal 8 karakter dengan 1 huruf besar dan 1 angka

            if (std::regex_match(pass_input, passRegex)) {
                mvprintw(8, 2, "Username dan password valid");
                refresh();
                std::this_thread::sleep_for(std::chrono::seconds(2));
                username->push_back(user_input);
                password->push_back(pass_input);
                clear();
                attron(COLOR_PAIR(1));
                mvprintw(2, 2, "\t\t\tLogin ke akun anda");
                mvprintw(4, 2, "Username anda: ");
                refresh();
                echo();
                getstr(&user_verification[0]);
                mvprintw(6, 2, "Password anda: ");
                refresh();
                echo();
                getstr(&pass_verification[0]);

                bool isVerified = false;
                for (size_t id = 0; id < username->size(); ++id) {
                  for (size_t access = 0; access < password->size(); access++) {
                    if ((*username)[id] == user_verification && (*password)[access] == pass_verification) {
                        isVerified = true;
                        break;
                    }
                  }
                }

                if (isVerified) {
                    mvprintw(8, 2, "Verifikasi berhasil, akun telah terdaftar.");
                    mvprintw(10, 2, "Masuk program...");
                    refresh();
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                    break;
                } else {
                    mvprintw(8, 2, "Verifikasi gagal, username atau password tidak cocok.");
                    mvprintw(10, 2, "Keluar dari halaman...");
                    refresh();
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                }
            } else {
                mvprintw(8, 2, "Password invalid, minimal 8 karakter dan 1 huruf besar dan 1 angka");
                refresh();
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
        } else {
            mvprintw(8, 2, "Username invalid, minimal 8 karakter dan 1 angka");
            refresh();
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }

        mvprintw(10, 2, "Ingin Registrasi kembali? (y/n)? ");
        refresh();
        echo();
        getnstr(&back, 1);
    } while (back == 'y' || back == 'Y');

    endwin();
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
