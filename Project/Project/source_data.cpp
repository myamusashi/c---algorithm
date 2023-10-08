#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include "source_data.h"

SourceData::SourceData(std::vector<std::string>* data, std::vector<std::string>* doWork, std::vector<std::string>* dataFinish)
    : mainData(data), toDo(doWork), taskSucced(dataFinish) {
}

void SourceData::AddTask(std::vector<std::string>* mainData) {
    std::vector<std::string> data;
    std::string daftar_tugas_baru;

    std::cout << "Tugas yang mau ditambahkan: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, daftar_tugas_baru);

    bool checkString = true;
    for (char c : daftar_tugas_baru) {
        if (!std::isalpha(c)) {
            checkString = false;
            break;
        }
    }

    if (checkString) {
        // Push ke vector mainData
        mainData->push_back(daftar_tugas_baru);
        std::cout << "Memproses tugas baru...\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));
        system("cls");
        std::cout << "Tugas baru: " << std::endl;
        for (int i = 0; i < mainData->size(); i++) { // Akses mainData
            std::cout << i << ") " << (*mainData)[i] << std::endl;
        }
    }
    else {
        std::cout << "Tidak boleh menggunakan angka atau karakter unik";
    }
}

void SourceData::TasktoDo(std::vector<std::string>* toDo) {
    /*
    Cara kode ini bekerja, data array yang dipilih untuk selesai akan di hapus di
    function mainData dan akan dipindahkan ke tugasSelesai
    */
    std::string completed_task;

    for (int i = 0; i < mainData->size(); i++) {
        std::cout << i << ") " << (*mainData)[i] << std::endl;
    }
    std::cout << "Tugas yang mau dikerjakan: ";
    int nomorTugasSelesai;
    // Menangani input pengguna yang tidak valid dengan instruksi if
    if (!(std::cin >> nomorTugasSelesai)) {
        std::cout << "Input tidak valid. Harap masukkan nomor tugas yang valid." << std::endl;
        std::cin.clear(); // Clean buffer input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else {
        if (nomorTugasSelesai >= 0 && nomorTugasSelesai < mainData->size()) {
            completed_task = (*mainData)[nomorTugasSelesai];
            mainData->erase(mainData->begin() + nomorTugasSelesai);
            toDo->push_back(completed_task);
            std::cout << "Memproses tugas selesai...\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
            system("cls");
            std::cout << "Tugas " << completed_task << " telah selesai" << std::endl;
        }
        else {
            std::cout << ("Nomor tugas tidak valid");
        }
    }
}

void SourceData::CompletedTask(std::vector<std::string>* taskSucced) {
    /*
    Cara kode ini bekerja, data array yang dipilih untuk selesai akan di hapus di
    function mainData dan akan dipindahkan ke tugasSelesai
    */
    std::string completed_task;

    for (int i = 0; i < mainData->size(); i++) {
        std::cout << i << ") " << (*mainData)[i] << std::endl;
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
        if (nomorTugasSelesai >= 0 && nomorTugasSelesai < mainData->size()) {
            completed_task = (*mainData)[nomorTugasSelesai];
            mainData->erase(mainData->begin() + nomorTugasSelesai);
            taskSucced->push_back(completed_task);
            std::cout << "Memproses tugas selesai...\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
            system("cls");
            std::cout << "Tugas " << completed_task << " telah selesai" << std::endl;
        }
        else {
            std::cout << ("Nomor tugas tidak valid");
        }
    }
}

void SourceData::DisplayTask(std::vector<std::string>* mainData) {
    std::cout << "Memproses data tugas... " << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    system("cls");
    std::cout << "Daftar tugas:\n";
    for (int i = 0; i < mainData->size(); i++) {
        std::cout << i << ") " << (*mainData)[i] << std::endl;
    }
}

void SourceData::DisplayCompletedTask(std::vector<std::string>* taskSucced) {
    std::cout << "Memproses data tugas yang sudah selesai... " << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    system("cls");
    std::cout << "Tugas yang sudah selesai:\n";
    for (int i = 0; i < taskSucced->size(); i++) {
        std::cout << i << ") " << (*taskSucced)[i] << std::endl;
    }
}

void SourceData::RemoveTask(std::vector<std::string>* mainData) {
    std::string tugasHapus;

    for (int i = 0; i < mainData->size(); i++) {
        std::cout << i << ") " << (*mainData)[i] << std::endl;
    }
    std::cout << "Tugas mana yang mau dihapus: ";
    int nomor_tugas;
    if (!(std::cin >> nomor_tugas)) {
        std::cout << "Input tidak valid, jangan gunakan karakter atau kata-kata unik";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else {
        if (nomor_tugas >= 0 && nomor_tugas <= mainData->size()) {
            mainData[nomor_tugas]; // Mengambil input nomor_tugas
            mainData->erase(mainData->begin() + nomor_tugas); // Menghapus nomor array yang dipilih
            std::cout << "Memproses tugas yang dihapus...\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
            std::cout << "Tugas " << tugasHapus << " Telah dihapus" << std::endl;
        }
        else {
            std::cout << ("Nomor tugas tidak valid");
        }
    }
}

void SourceData::RemoveFinishTask(std::vector<std::string>* taskSucced) {
    std::string tugasHapus;

    for (int i = 0; i < taskSucced->size(); i++) {
        std::cout << i << ") " << (*taskSucced)[i] << std::endl;
    }
    std::cout << "Tugas mana yang mau dihapus: ";
    int nomor_tugas;
    if (!(std::cin >> nomor_tugas)) {
        std::cout << "Input tidak valid, jangan gunakan karakter atau kata-kata unik";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else {
        if (nomor_tugas >= 0 && nomor_tugas <= taskSucced->size()) {
            taskSucced[nomor_tugas]; // Mengambil input nomor_tugas
            taskSucced->erase(taskSucced->begin() + nomor_tugas); // Menghapus nomor array yang dipilih
            std::cout << "Memproses tugas yang dihapus...\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
            std::cout << "Tugas " << tugasHapus << " Telah dihapus" << std::endl;
        }
        else {
            std::cout << ("Nomor tugas tidak valid");
        }
    }
}

void SourceData::EditTask(std::vector<std::string>* mainData) {
    /*
    Fungsi "editTugas" adalah mengambil input int
    untuk meminta nomor yang dipilih untuk di edit dan mengecek
    apakah tugas yang diedit ada di mainData jika ada, maka menunggu
    user memasukkan string baru untuk menggantikan tugas yang lama
    dan memperlihatkan tugas yang sudah di edit
    */
    for (int i = 0; i < mainData->size(); i++) {
        std::cout << i << ") " << (*mainData)[i] << std::endl;
    }
    std::cout << "Tugas mana yang mau di edit: ";
    int editTugas;
    if (!(std::cin >> editTugas)) {
        std::cout << "Input tidak valid, jangan gunakan karakter atau kata-kata unik!";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else {
        if (editTugas >= 0 && editTugas < mainData->size()) {
            std::cout << "Edit tugas: ";
            std::cin >> (*mainData)[editTugas];
            std::cout << "Memproses tugas yang di edit...\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
            system("cls");
            for (int i = 0; i < mainData->size(); i++) {
                std::cout << i << ") " << (*mainData)[i] << std::endl;
            }
        }
        else {
            std::cout << ("Nomor tugas invalid");
        }
    }
}

void SourceData::EditFinishTask(std::vector<std::string>* taskSucced) {
    for (int i = 0; i < taskSucced->size(); i++) {
        std::cout << i << ") " << (*mainData)[i] << std::endl;
    }
    std::cout << "Tugas mana yang mau di edit: ";
    int editTugas;
    if (!(std::cin >> editTugas)) {
        std::cout << "Input tidak valid, jangan gunakan karakter atau kata-kata unik!";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else {
        if (editTugas >= 0 && editTugas < taskSucced->size()) {
            std::cout << "Edit tugas: ";
            std::cin >> (*taskSucced)[editTugas];
            std::cout << "Memproses tugas yang di edit...\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
            system("cls");
            for (int i = 0; i < taskSucced->size(); i++) {
                std::cout << i << ") " << (*taskSucced)[i] << std::endl;
            }
        }
        else {
            std::cout << ("Nomor tugas invalid");
        }
    }
}