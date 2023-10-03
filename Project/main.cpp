#include <cctype>
#include <chrono>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>
#include "login.h" 

std::vector<std::string> mainData
{
 "matematika",           "Fisika dasar",
 "logika pemrograman",   "bahasa indonesia",
 "Basic english",        "PJOK",
 "Pendidikan pancasila", "agama",
 "project kelompok",     "english TOEFL"
};

void addTask() {
    std::string daftar_tugas_baru;
    /*
    Membuat exception handling untuk mengatasi ketika User salah input. Input yang diberikan tidak langsung
    masuk ke mainData dan user akan kena peringatan ketika salah memasukkan input
    */
    try {
        std::cout << "Tugas yang mau ditambahkan: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // Membersihkan buffer input untuk tidak menciptakan unexpected error ketika
        // user salah memasukkan input
        std::getline(std::cin, daftar_tugas_baru);
        bool checkString = true;
        for (char c : daftar_tugas_baru) {
            if (!std::isdigit(c)) {
                checkString = false;
                break;
            }
            else {
                throw "Tidak boleh menggunakan nomor atau karakter unik";
            }
        }
        mainData.push_back(daftar_tugas_baru); // Push ke vector mainData
        std::cout << "Memproses tugas baru...\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));
        system("cls");
        std::cout << "Tugas baru: " << std::endl;
        for (int i = 0; i < mainData.size(); i++) {
            std::cout << i << ") " << mainData[i] << std::endl;
        }
    }
    catch (const char* denied) {
        std::cout << "Input error: " << denied;
    }
}

std::vector<std::string> tugasSelesai{
    // I N V I S I B L E D A T A 
};

void CompletedTask() {
    /*
    Cara kode ini bekerja, data array yang dipilih untuk selesai akan di hapus di
    function mainData dan akan dipindahkan ke tugasSelesai
    */
    std::string completed_task;

    for (int i = 0; i < mainData.size(); i++) {
        std::cout << i << ") " << mainData[i] << std::endl;
    }
    std::cout << "Tugas yang sudah selesai: ";
    int nomorTugasSelesai;
    // Menangani input pengguna yang tidak valid dengan instruksi if
    if (!(std::cin >> nomorTugasSelesai)) {
        std::cout << "Input tidak valid. Harap masukkan nomor tugas yang valid." << std::endl;
        std::cin.clear(); // Clean buffer input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else {
        try {
            if (nomorTugasSelesai >= 0 && nomorTugasSelesai < mainData.size()) {
                completed_task = mainData[nomorTugasSelesai];
                mainData.erase(mainData.begin() + nomorTugasSelesai);
                tugasSelesai.push_back(completed_task);
                std::cout << "Memproses tugas selesai...\n";
                std::this_thread::sleep_for(std::chrono::seconds(3));
                system("cls");
                std::cout << "Tugas " << completed_task << " telah selesai" << std::endl;
            }
            else {
                throw std::invalid_argument("Nomor tugas tidak valid");
            }
        }
        catch (const std::exception& e) {
            std::cout << "Input error: " << e.what();
        }
    }
}

void viewTask() {
    std::cout << "Memproses data tugas... " << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    system("cls");
    for (int i = 0; i < mainData.size(); i++) {
        std::cout << i << ") " << mainData[i] << std::endl;
    }
}

void viewFinishTask() {
    std::cout << "Memproses data tugas yang sudah selesai... " << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    system("cls");
    for (int i = 0; i < tugasSelesai.size(); i++) {
        std::cout << i << ") " << tugasSelesai[i] << std::endl;
    }
}

void removeTask() {
    std::string tugasHapus;

    for (int i = 0; i < mainData.size(); i++) {
        std::cout << i << ") " << mainData[i] << std::endl;
    }
    std::cout << "Tugas mana yang mau dihapus: ";
    int nomor_tugas;
    if (!(std::cin >> nomor_tugas)) {
        std::cout << "Input tidak valid, jangan gunakan karakter atau kata-kata unik";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
       try {
            if (nomor_tugas >= 0 && nomor_tugas <= mainData.size()) {
                tugasHapus = mainData[nomor_tugas]; // Mengambil input nomor_tugas
                mainData.erase(mainData.begin() + nomor_tugas); // Menghapus nomor array yang dipilih
                std::cout << "Memproses tugas yang dihapus...\n";
                std::this_thread::sleep_for(std::chrono::seconds(3));
                std::cout << "Tugas " << tugasHapus << " Telah dihapus" << std::endl;
            }
            else {
                throw std::invalid_argument("Nomor tugas tidak valid");
            }
        }
       catch (const std::exception& e) {
            std::cout << "Input error: " << e.what();
        }
    }
}

void editTask() {
    /*
    Fungsi "editTugas" adalah mengambil input int
    untuk meminta nomor yang dipilih untuk di edit dan mengecek
    apakah tugas yang diedit ada di mainData jika ada, maka menunggu
    user memasukkan string baru untuk menggantikan tugas yang lama
    dan memperlihatkan tugas yang sudah di edit
    */
    for (int i = 0; i < mainData.size(); i++) {
        std::cout << i << ") " << mainData[i] << std::endl;
    }
    std::cout << "Tugas mana yang mau di edit: ";
    int editTugas;
    if (!(std::cin >> editTugas)) {
        std::cout << "Input tidak valid, jangan gunakan karakter atau kata-kata unik!";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
        try {
            if (editTugas >= 0 && editTugas < mainData.size()) {
                std::cout << "Edit tugas: ";
                std::cin >> mainData[editTugas];
                std::cout << "Memproses tugas yang di edit...\n";
                std::this_thread::sleep_for(std::chrono::seconds(3));
                system("cls");
                for (int i = 0; i < mainData.size(); i++) {
                    std::cout << i << ") " << mainData[i] << std::endl;
                }
            }
            else {
                throw std::invalid_argument("Nomor tugas invalid");
            }
        }
        catch (const std::exception& e) {
            std::cout << "Input error: " << e.what();
        }
    }
    
}

int main(int argc, const char** argv) {

    std::string user_verification;
    int pass_verification;
    char pilihan;
    char ulang;

    system("cls");
    std::cout << "\t\t\t***********************************************************************" << std::endl;
    std::cout << "\t\t\t                       Pengelolaan Daftar Tugas                        " << std::endl;
    std::cout << "\t\t\t***********************************************************************\n\n" << std::endl;
    // Sign-up 
    
    // Login
    // std::cout << "Login ke program: ";
    // std::cin >> user_verification;
    // std::cout << "Masukkan password: ";
    // std::cin >> pass_verification;
    // if (user_verification == username && pass_verification == password) {
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
        std::cout << "7) Keluar dari program\n";
        std::cout << "Pilih menu yang mau anda lakukan(1-7): ";
        std::cin >> pilihan;

        switch (pilihan) {
        case '1':
            system("cls");
            addTask();
            break;
        case '2':
            system("cls");
            CompletedTask();
            break;
        case '3':
            system("cls");
            viewTask();
            break;
        case '4':
            system("cls");
            viewFinishTask();
            break;
        case '5':
            system("cls");
            removeTask();
            break;
        case '6':
            system("cls");
            editTask();
            break;
        case '7':
            return 0;
        default: {
            std::cout << "Pilihan anda tidak ada";
        }
        }
        std::cout << std::endl;
        std::cout << "Ingin memilih menu lain(y/n)? ";
        std::cin >> ulang;
        system("cls");
    } while (ulang != 'n');
    // } else {

    // }
    return 0;
}
