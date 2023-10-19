#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include "processes.h"

SourceData::SourceData(std::vector<std::string>* data, std::vector<std::string>* dataFinish, std::vector<std::string>* doWork)
    : mainData(data), taskSucced(dataFinish), toDo(doWork) {
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
            std::cout << i << ") " << (*mainData)[i] << "\n";
        }
    }
    else {
        std::cout << "Tidak boleh menggunakan angka atau karakter unik";
    }
}

void SourceData::TasktoDo(std::vector<std::string>* toDo) {
    /*
    Cara kode ini bekerja, data array yang dipilih untuk selesai akan di hapus di
    function mainData dan akan dipindahkan ke toDo yang ada di file source_data.h
    */
    std::string taskWork;

    for (int i = 0; i < mainData->size(); i++) {
        std::cout << i << ") " << (*mainData)[i] << "\n";
    }
    std::cout << "Tugas yang mau dikerjakan: ";
    int nomorTugasDikerjakan;

    // Menangani input pengguna yang tidak valid dengan instruksi if
    if (!(std::cin >> nomorTugasDikerjakan)) {
        std::cout << "Input tidak valid. Harap masukkan nomor tugas yang valid." << "\n";
        std::cin.clear(); // Clean buffer input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else {
        if (nomorTugasDikerjakan >= 0 && nomorTugasDikerjakan < mainData->size()) {
            taskWork = (*mainData)[nomorTugasDikerjakan];

            mainData->erase(mainData->begin() + nomorTugasDikerjakan);
            toDo->push_back(taskWork);
            std::cout << "Memproses tugas yang akan dikerjakan...\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
            system("cls");
            std::cout << "Tugas " << taskWork << " akan dikerjakan" << "\n";
        }
        else {
            std::cout << ("Nomor tugas tidak valid");
        }
    }
}

void SourceData::CompletedTask(std::vector<std::string>* taskSucced) {
    /*
    Cara kode ini bekerja, data array yang dipilih untuk selesai akan di hapus di
    function mainData dan akan dipindahkan ke taskSucced
    */
    std::string completed_task;

    for (int i = 0; i < toDo->size(); i++) {
        std::cout << i << ") " << (*toDo)[i] << "\n";
    }
    std::cout << "Tugas yang sudah selesai: ";
    int nomorTugasSelesai;
    // Menangani input pengguna yang tidak valid dengan instruksi if
    if (!(std::cin >> nomorTugasSelesai)) {
        std::cout << "Input tidak valid. Harap masukkan nomor tugas yang valid." << "\n";
        std::cin.clear(); // Clean buffer input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else {
        if (nomorTugasSelesai >= 0 && nomorTugasSelesai < toDo->size()) {
            completed_task = (*toDo)[nomorTugasSelesai];

            toDo->erase(toDo->begin() + nomorTugasSelesai);
            taskSucced->push_back(completed_task);
            std::cout << "Memproses tugas selesai...\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
            system("cls");
            std::cout << "Tugas " << completed_task << " telah selesai" << "\n";
        }
        else {
            std::cout << ("Nomor tugas tidak valid");
        }
    }
}

void SourceData::DisplayTask(std::vector<std::string>* mainData) {
    std::cout << "Memproses data tugas... " << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    system("cls");
    std::cout << "Daftar tugas:\n";
    for (int i = 0; i < mainData->size(); i++) {
        std::cout << i << ") " << (*mainData)[i] << "\n";
    }
}

void SourceData::DisplayTaskToDo(std::vector<std::string>* toDo) {
    std::cout << "Memproses data tugas yang sedang dikerjakan... " << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    system("cls");
    std::cout << "Daftar tugas:\n";
    for (int i = 0; i < toDo->size(); i++) {
        std::cout << i << ") " << (*toDo)[i] << "\n";
    }
}

void SourceData::DisplayCompletedTask(std::vector<std::string>* taskSucced) {
    std::cout << "Memproses data tugas yang sudah selesai... " << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    system("cls");
    std::cout << "Tugas yang sudah selesai:\n";
    for (int i = 0; i < taskSucced->size(); i++) {
        std::cout << i << ") " << (*taskSucced)[i] << "\n";
    }
}

void SourceData::RemoveTask(std::vector<std::string>* mainData) {
    std::string tugasHapus;

    for (int i = 0; i < mainData->size(); i++) {
        std::cout << i << ") " << (*mainData)[i] << "\n";
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
            mainData->erase(mainData->begin() + nomor_tugas); // Menghapus nomor array yang dipilih
            std::cout << "Memproses tugas yang dihapus...\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
            std::cout << "Tugas " << tugasHapus << " Telah dihapus" << "\n";
        }
        else {
            std::cout << ("Nomor tugas tidak valid");
        }
    }
}

void SourceData::RemoveTaskToDo(std::vector<std::string>* toDo) {
    std::string tugasHapus;

    for (int i = 0; i < toDo->size(); i++) {
        std::cout << i << ") " << (*toDo)[i] << "\n";
    }
    std::cout << "Tugas mana yang mau dihapus: ";
    int nomor_tugas;
    if (!(std::cin >> nomor_tugas)) {
        std::cout << "Input tidak valid, jangan gunakan karakter atau kata-kata unik";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else {
        if (nomor_tugas >= 0 && nomor_tugas <=toDo->size()) {
            toDo->erase(toDo->begin() + nomor_tugas); // Menghapus nomor array yang dipilih
            std::cout << "Memproses tugas yang dihapus...\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
            std::cout << "Tugas " << tugasHapus << " Telah dihapus" << "\n";
        }
        else {
            std::cout << ("Nomor tugas tidak valid");
        }
    }
}

void SourceData::RemoveFinishTask(std::vector<std::string>* taskSucced) {
    std::string tugasHapus;

    for (int i = 0; i < taskSucced->size(); i++) {
        std::cout << i << ") " << (*taskSucced)[i] << "\n";
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
            taskSucced->erase(taskSucced->begin() + nomor_tugas); // Menghapus nomor array yang dipilih
            std::cout << "Memproses tugas yang dihapus...\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
            std::cout << "Tugas " << tugasHapus << " Telah dihapus" << "\n";
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
        std::cout << i << ") " << (*mainData)[i] << "\n";
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
                std::cout << i << ") " << (*mainData)[i] << "\n";
            }
        }
        else {
            std::cout << ("Nomor tugas invalid");
        }
    }
}

void SourceData::EditTaskTodo(std::vector<std::string>* toDo) {
    for (int i = 0; i < toDo->size(); i++) {
        std::cout << i << ") " << (*toDo)[i] << "\n";
    }
    std::cout << "Tugas mana yang mau di edit: ";
    int editTugas;
    if (!(std::cin >> editTugas)) {
        std::cout << "Input tidak valid, jangan gunakan karakter atau kata-kata unik!";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else {
        if (editTugas >= 0 && editTugas < toDo->size()) {
            std::cout << "Edit tugas: ";
            std::cin >> (*toDo)[editTugas];
            std::cout << "Memproses tugas yang di edit...\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
            system("cls");
            for (int i = 0; i < toDo->size(); i++) {
                std::cout << i << ") " << (*toDo)[i] << "\n";
            }
        }
        else {
            std::cout << ("Nomor tugas invalid");
        }
    }
}

void SourceData::EditFinishTask(std::vector<std::string>* taskSucced) {
    for (int i = 0; i < taskSucced->size(); i++) {
        std::cout << i << ") " << (*mainData)[i] << "\n";
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
                std::cout << i << ") " << (*taskSucced)[i] << "\n";
            }
        }
        else {
            std::cout << ("Nomor tugas invalid");
        }
    }
}
