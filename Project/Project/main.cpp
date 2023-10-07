#include <iostream>
#include <string>
#include <vector>
#include "data_login.h" 
#include "source_data.h"

int main(int argc, const char** argv) {

    std::vector<std::string> id, data;
    std::vector<std::string> access, dataFinish;

    // Membuat objek UserPass dan SourceData
    SourceData s(&data, &dataFinish);
    UserPass c(&id, &access);
    
    // Memanggil metode ProcessRegis untuk proses pendaftaran
    c.ProcessRegister();

    char pilihan;
    char ulang;

    system("cls");
    std::cout << "\t\t\t***********************************************************************" << std::endl;
    std::cout << "\t\t\t                       Pengelolaan Daftar Tugas                        " << std::endl;
    std::cout << "\t\t\t***********************************************************************\n\n" << std::endl;

    do {
        std::cout << "\n\nLanjut\n";
        std::cout << "Menu Utama\n" << std::endl;
        std::cout << "Apa yang mau anda lakukan" << std::endl;
        std::cout << "1) Mau membuat list tugas baru\n";
        std::cout << "2) Mau menandai tugas\n";
        std::cout << "3) Mau menampilkan tugas sekarang\n";
        std::cout << "4) Menampilkan tugas yang sudah selesai\n";
        std::cout << "5) Mau menghapus tugas\n";
        std::cout << "6) Mau mengedit tugas\n";
        std::cout << "7) Mau logout dari program?\n";
        std::cout << "8) Mau registrasi akun baru?\n";
        std::cout << "9) Keluar dari program\n";
        std::cout << "Pilih menu yang mau anda lakukan(1-9): ";
        std::cin >> pilihan;

        switch (pilihan) {
        case '1':
            system("cls");
            s.AddData(&data); // Memanggil void function
            break;
        case '2':
            system("cls");
            s.CompletedData(&dataFinish);
            break;
        case '3':
            system("cls");
            s.DisplayData(&data);
            break;
        case '4':
            system("cls");
            s.DisplayFinishData(&dataFinish);
            break;
        case '5':
            system("cls");
            s.RemoveData(&data, &dataFinish);
            break;
        case '6':
            system("cls");
            s.EditData(&data, &dataFinish);
            break;
        case '7':
            system("cls");
            c.LoginProgram();
            break;
        case '8':
            system("cls");
            c.ProcessRegister();
            break;
        case '9':
            exit(1);
        default:
            std::cout << "Pilihan anda tidak ada";
        }
        std::cout << std::endl;
        std::cout << "Ingin ulang lagi atau melanjutkan (u/l)? ";
        std::cin >> ulang;
    } while (ulang != 'u');
    return 0;
}