#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <ncurses.h>
#include "processes.h" 
#include "credentials.h"

int main(int argc, const char** argv) {
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::vector<std::string> data, doWork, dataFinish;
    std::vector<std::string> id, access;

    // Membuat objek UserPass dan SourceData
    SourceData s(&data, &dataFinish, &doWork);
    UserPass c(&id, &access);
    
    // Memanggil metode ProcessRegister untuk proses pendaftaran
    c.ProcessRegister();

    int pilihan;
    char ulang;

    system("cls");
    std::cout << "\t\t\t***********************************************************************" << std::endl;
    std::cout << "\t\t\t                       Pengelolaan Daftar Tugas                        " << std::endl;
    std::cout << "\t\t\t***********************************************************************\n\n" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    do {
        system("cls");
        std::cout << "Menu Utama\n\n";
        std::cout << "Apa yang mau anda lakukan\n";
        std::cout << "1) Mau membuat list tugas baru?\n";
        std::cout << "2) Mau menandai tugas yang mau dikerjakan?\n";
        std::cout << "3) Mau menandai tugas selesai?\n";
        std::cout << "4) Menampilkan tugas sekarang\n";
        std::cout << "5) Menampilkan tugas yang sedang dikerjakan\n";
        std::cout << "6) Menampilkan tugas yang sudah selesai\n";
        std::cout << "7) Mau menghapus tugas sekarang?\n";
        std::cout << "8) Mau menghapus tugas yang sedang dikerjakan?\n";
        std::cout << "9) Mau menghapus tugas yang sudah selesai?\n";
        std::cout << "10) Mau mengedit tugas\n";
        std::cout << "11) Mau mengedit tugas yang sedang dikerjakan?\n";
        std::cout << "12) Mau mengedit tugas yang sudah selesai?\n";
        std::cout << "13) Mau logout dari program?\n";
        std::cout << "14) Mau registrasi akun baru?\n";
        std::cout << "15) Keluar dari program\n";
        std::cout << "Pilih menu yang mau anda lakukan(1-15): ";
        std::cin >> pilihan;

        switch (pilihan) {
        case 1:
            system("cls");
            s.AddTask(&data);
            break;
        case 2:
            system("cls");
            s.TasktoDo(&doWork);
            break;
        case 3:
            system("cls");
            s.CompletedTask(&dataFinish);
            break;
        case 4:
            system("cls");
            s.DisplayTask(&data);
            break;
        case 5:
            system("cls");
            s.DisplayTaskToDo(&doWork);
            break;
        case 6:
            system("cls");
            s.DisplayCompletedTask(&dataFinish);
            break;
        case 7:
            system("cls");
            s.RemoveTask(&data);
            break;
        case 8:
            system("cls");
            s.RemoveTaskToDo(&doWork);
            break;
        case 9:
            system("cls");
            s.RemoveFinishTask(&dataFinish);
            break;
        case 10:
            system("cls");
            s.EditTask(&data);
            break;
        case 11:
            system("cls");
            s.EditTaskTodo(&doWork);
            break;
        case 12:
            system("cls");
            s.EditFinishTask(&dataFinish);
            break;
        case 13:
            system("cls");
            c.LoginProgram();
            break;
        case 14:
            system("cls");
            c.ProcessRegister();
            break;
        case 15:
            std::cout << "Anda memilih keluar...";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            return 0;
        default:
            std::cout << "Pilihan anda tidak ada";
        }
        std::cout << std::endl;
        std::cout << "1) Lanjut\n" << "2) Keluar\n";
        std::cout << "Ingin lanjut ke program atau keluar? ";
        std::cin >> ulang;
    } while (ulang != '2');
    return 0;
}
