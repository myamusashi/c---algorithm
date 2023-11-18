#include "../headers/processes.h"

#include <boost/algorithm/string.hpp>
#include <chrono>
#include <exception>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <system_error>
#include <thread>

#include "bsoncxx/builder/basic/document.hpp"
#include "bsoncxx/builder/basic/kvp.hpp"
#include "bsoncxx/document/element.hpp"

using namespace bsoncxx;

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;

SourceData::SourceData(const std::string &conn, const std::string &dbs,
                       const std::string &taskqueue, const std::string &taskstodo,
                       const std::string &finishedtasks)
    : connection_(mongocxx::uri(conn)),
      database_(connection_[dbs]),
      newTasks_(database_[taskqueue]),
      inProgress_(database_[taskstodo]),
      completedTask_(database_[finishedtasks]) {
    // Doing something here, if necessary
}

void SourceData::AddTask() {
    std::string task, subject, dosen, category;
    const int max_length = 150;  // batas maksimal panjang input

    std::cout << "Nama tugas: ";
    std::cin.ignore();
    std::getline(std::cin, task);     // baca input sebagai string
    while (task.size() > max_length)  // periksa panjang string
    {
        std::cout << "Input terlalu panjang, maksimal 150 karakter.\n";
        std::cout << "Nama tugas: ";
        std::getline(std::cin, task);  // baca input lagi
    }
    boost::algorithm::trim(task);
    std::cout << "\nMata pelajaran: ";
    std::getline(std::cin, subject);     // baca input sebagai string
    while (subject.size() > max_length)  // periksa panjang string
    {
        std::cout << "Input terlalu panjang, maksimal 150 karakter.\n";
        std::cout << "Mata pelajaran: ";
        std::getline(std::cin, subject);  // baca input lagi
    }
    boost::algorithm::trim(subject);

    std::cout << "\nDosen pengajar: ";
    std::getline(std::cin, dosen);     // baca input sebagai string
    while (dosen.size() > max_length)  // periksa panjang string
    {
        std::cout << "Input terlalu panjang, maksimal 150 karakter.\n";
        std::cout << "Dosen pengajar: ";
        std::getline(std::cin, dosen);  // baca input lagi
    }
    boost::algorithm::trim(dosen);

    std::cout << "\nKategori pelajaran (wajib/tambahan): ";
    std::getline(std::cin, category);     // baca input sebagai string
    while (category.size() > max_length)  // periksa panjang string
    {
        std::cout << "Input terlalu panjang, maksimal 150 karakter.\n";
        std::cout << "Kategori pelajaran (wajib/tambahan): ";
        std::getline(std::cin, category);  // baca input lagi
    }
    boost::algorithm::trim(category);

    std::cout << "Memproses tugas baru...\n";
    // Providing a seed value
    srand((unsigned)time(NULL));

    // Get a random number
    int random = 1000 + (rand() % 5000);

    // Assume that task, subject, dosen, category are stringssrc/crede
    auto add_doc =
        make_document(kvp("no", random), kvp("task", task), kvp("subject", subject),
                      kvp("dosen", dosen), kvp("category", category), kvp("completed", false));
    // Use insert_one to insert a single document

    auto result = newTasks_.insert_one(add_doc.view());
    try {
        for (auto &&element : add_doc) {
            if (result->result().inserted_count() == 1 &&
                element.type() == bsoncxx::type::k_int32) {
                std::cout << "Tugas berhasil ditambahkan\n";
                std::cout << element.key() << ": " << element.get_int32().value << "\n";
            }
        }
    } catch (const std::system_error &e) {
        std::cout << "ada kesalahan saat memasukkan tugas!";
        std::cout << "error code: " << e.code() << std::endl;
        std::cout << "error message: " << e.what() << std::endl;
        if (e.code().category() == std::system_category() && e.code().value() == 10050) {
            std::cout << "Koneksi internet anda mati atau tidak bagus" << std::endl;
        }
    }
}

void SourceData::TasktoDo() {
    /*
    Cara kode ini bekerja, data array yang dipilih untuk selesai akan di
    hapus di function mainData dan akan dipindahkan ke toDo yang ada di file
    source_data.h
    */
    std::string taskWork;

    std::cout << "\033[2J\033[1;1H";
    auto cursor_all = newTasks_.find({});
    try {
        for (auto &&doc : cursor_all) {
            for (document::element &element : doc) {
                if (element.type() == bsoncxx::type::k_int32) {
                    std::cout << element.key() << ": " << element.get_int32().value << std::endl;
                }
                if (element.type() == bsoncxx::type::k_utf8) {
                    std::cout << element.key() << ": " << element.get_string().value.to_string()
                              << std::endl;
                }
                if (element.type() == bsoncxx::type::k_bool) {
                    bool bool_value = element.get_bool().value;
                    std::string bool_str = bool_value ? "sudah" : "belum";
                    std::cout << element.key() << ": " << bool_str << "\n";
                }
            }
            std::cout << "------------------------------------------------\n";
        }
    } catch (const std::exception &ex) {
        std::cerr << "Terjadi kesalahan memproses tugas, contoh(No: {task}): " << ex.what();
    }
    int id;
    std::cout << "Tugas yang mau dikerjakan (masukkan nomor tugas): ";
    std::cin >> id;
   
  auto&& find_document = newTasks_.find_one(make_document(kvp("no",id)));
  if (!(find_document)) {
    std::cout << "Document yang anda cari tidak ada disini!\n";
  } else {
    std::cout << "Document anda terdaftar di koleksi kami!\n";
    std::cout << "Memproses document anda ke koleksi inProgress\n";

    auto&& insert = find_document->view();
    inProgress_.insert_one(insert);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    newTasks_.delete_one(make_document(kvp("no",id)));
    std::cout << "Dokumen telah masuk ke inProgress";
  }
}
void SourceData::CompletedTask() {
    /*
    Cara kode ini bekerja, data array yang dipilih untuk selesai akan di
    hapus di function mainData dan akan dipindahkan ke taskSucced
    */
    std::cout << "\033[2J\033[1;1H";
    auto cursor_all = inProgress_.find({});
    try {
        for (auto &&doc : cursor_all) {
            for (document::element &element : doc) {
                if (element.type() == bsoncxx::type::k_int32) {
                    std::cout << element.key() << ": " << element.get_int32().value << std::endl;
                }
                if (element.type() == bsoncxx::type::k_utf8) {
                    std::cout << element.key() << ": " << element.get_string().value.to_string()
                              << std::endl;
                }
                if (element.type() == bsoncxx::type::k_bool) {
                    bool bool_value = element.get_bool().value;
                    std::string bool_str = bool_value ? "sudah" : "belum";
                    std::cout << element.key() << ": " << bool_str << "\n";
                }
            }
            std::cout << "------------------------------------------------\n";
        }
    } catch (const std::exception &ex) {
        std::cerr << "Terjadi kesalahan memproses tugas, contoh(No: {task}): " << ex.what();
    }
    int id;
    std::cout << "Tugas yang mau dikerjakan (masukkan nomor tugas): ";
    std::cin >> id;
   
  auto&& find_document = inProgress_.find_one(make_document(kvp("no",id)));
  if (!(find_document)) {
    std::cout << "Document yang anda cari tidak ada disini!\n";
  } else {
    std::cout << "Document anda terdaftar di koleksi kami!\n";
    std::cout << "Memproses document anda ke koleksi inProgress\n";

    auto&& insert = find_document->view();
    completedTask_.insert_one(insert);
    
    std::cout << "Dokumen telah masuk ke inProgress";
  }
}
// void SourceData::DisplayTask() {
//     std::cout << "Memproses data tugas... " << "\n";
//     std::this_thread::sleep_for(std::chrono::seconds(1));
//     system("cls");
//     std::cout << "Daftar tugas:\n";
//     for (int i = 0; i < mainData->size(); i++) {
//         std::cout << i << ") " << (*mainData)[i] << "\n";
//     }
// }

// void SourceData::DisplayTaskToDo() {
//     std::cout << "Memproses data tugas yang sedang dikerjakan... " << "\n";
//     std::this_thread::sleep_for(std::chrono::seconds(1));
//     system("cls");
//     std::cout << "Daftar tugas:\n";
//     for (int i = 0; i < toDo->size(); i++) {
//         std::cout << i << ") " << (*toDo)[i] << "\n";
//     }
// }

// void SourceData::DisplayCompletedTask() {
//     std::cout << "Memproses data tugas yang sudah selesai... " << "\n";
//     std::this_thread::sleep_for(std::chrono::seconds(1));
//     system("cls");
//     std::cout << "Tugas yang sudah selesai:\n";
//     for (int i = 0; i < taskSucced->size(); i++) {
//         std::cout << i << ") " << (*taskSucced)[i] << "\n";
//     }
// }

// void SourceData::RemoveTask() {
//     std::string tugasHapus;

//     for (int i = 0; i < mainData->size(); i++) {
//         std::cout << i << ") " << (*mainData)[i] << "\n";
//     }
//     std::cout << "Tugas mana yang mau dihapus: ";
//     int nomor_tugas;
//     if (!(std::cin >> nomor_tugas)) {
//         std::cout << "Input tidak valid, jangan gunakan karakter atau
//         kata-kata unik"; std::cin.clear();
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//     }
//     else {
//         if (nomor_tugas >= 0 && nomor_tugas <= mainData->size()) {
//             mainData->erase(mainData->begin() + nomor_tugas); // Menghapus
//             nomor array yang dipilih std::cout << "Memproses tugas yang
//             dihapus...\n";
//             std::this_thread::sleep_for(std::chrono::seconds(3));
//             std::cout << "Tugas " << tugasHapus << " Telah dihapus" << "\n";
//         }
//         else {
//             std::cout << ("Nomor tugas tidak valid");
//         }
//     }
// }

// void SourceData::RemoveTaskToDo() {
//     std::string tugasHapus;

//     for (int i = 0; i < toDo->size(); i++) {
//         std::cout << i << ") " << (*toDo)[i] << "\n";
//     }
//     std::cout << "Tugas mana yang mau dihapus: ";
//     int nomor_tugas;
//     if (!(std::cin >> nomor_tugas)) {
//         std::cout << "Input tidak valid, jangan gunakan karakter atau
//         kata-kata unik"; std::cin.clear();
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//     }
//     else {
//         if (nomor_tugas >= 0 && nomor_tugas <=toDo->size()) {
//             toDo->erase(toDo->begin() + nomor_tugas); // Menghapus nomor
//             array yang dipilih std::cout << "Memproses tugas yang
//             dihapus...\n";
//             std::this_thread::sleep_for(std::chrono::seconds(3));
//             std::cout << "Tugas " << tugasHapus << " Telah dihapus" << "\n";
//         }
//         else {
//             std::cout << ("Nomor tugas tidak valid");
//         }
//     }
// }

// void SourceData::RemoveFinishTask() {
//     std::string tugasHapus;

//     for (int i = 0; i < taskSucced->size(); i++) {
//         std::cout << i << ") " << (*taskSucced)[i] << "\n";
//     }
//     std::cout << "Tugas mana yang mau dihapus: ";
//     int nomor_tugas;
//     if (!(std::cin >> nomor_tugas)) {
//         std::cout << "Input tidak valid, jangan gunakan karakter atau
//         kata-kata unik"; std::cin.clear();
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//     }
//     else {
//         if (nomor_tugas >= 0 && nomor_tugas <= taskSucced->size()) {
//             taskSucced->erase(taskSucced->begin() + nomor_tugas); //
//             Menghapus nomor array yang dipilih std::cout << "Memproses tugas
//             yang dihapus...\n";
//             std::this_thread::sleep_for(std::chrono::seconds(3));
//             std::cout << "Tugas " << tugasHapus << " Telah dihapus" << "\n";
//         }
//         else {
//             std::cout << ("Nomor tugas tidak valid");
//         }
//     }
// }

// void SourceData::EditTask() {
//     /*
//     Fungsi "editTugas" adalah mengambil input int
//     untuk meminta nomor yang dipilih untuk di edit dan mengecek
//     apakah tugas yang diedit ada di mainData jika ada, maka menunggu
//     user memasukkan string baru untuk menggantikan tugas yang lama
//     dan memperlihatkan tugas yang sudah di edit
//     */
//     for (int i = 0; i < mainData->size(); i++) {
//         std::cout << i << ") " << (*mainData)[i] << "\n";
//     }
//     std::cout << "Tugas mana yang mau di edit: ";
//     int editTugas;
//     if (!(std::cin >> editTugas)) {
//         std::cout << "Input tidak valid, jangan gunakan karakter atau
//         kata-kata unik!"; std::cin.clear();
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//     }
//     else {
//         if (editTugas >= 0 && editTugas < mainData->size()) {
//             std::cout << "Edit tugas: ";
//             std::cin >> (*mainData)[editTugas];
//             std::cout << "Memproses tugas yang di edit...\n";
//             std::this_thread::sleep_for(std::chrono::seconds(3));
//             system("cls");
//             for (int i = 0; i < mainData->size(); i++) {
//                 std::cout << i << ") " << (*mainData)[i] << "\n";
//             }
//         }
//         else {
//             std::cout << ("Nomor tugas invalid");
//         }
//     }
// }

// void SourceData::EditTaskTodo() {
//     for (int i = 0; i < toDo->size(); i++) {
//         std::cout << i << ") " << (*toDo)[i] << "\n";
//     }
//     std::cout << "Tugas mana yang mau di edit: ";
//     int editTugas;
//     if (!(std::cin >> editTugas)) {
//         std::cout << "Input tidak valid, jangan gunakan karakter atau
//         kata-kata unik!"; std::cin.clear();
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//     }
//     else {
//         if (editTugas >= 0 && editTugas < toDo->size()) {
//             std::cout << "Edit tugas: ";
//             std::cin >> (*toDo)[editTugas];
//             std::cout << "Memproses tugas yang di edit...\n";
//             std::this_thread::sleep_for(std::chrono::seconds(3));
//             system("cls");
//             for (int i = 0; i < toDo->size(); i++) {
//                 std::cout << i << ") " << (*toDo)[i] << "\n";
//             }    void TasktoDo(const std::string& inProgress_);
//         }
//         else {
//             std::cout << ("Nomor tugas invalid");
//         }
//     }
// }

// void SourceData::EditFinishTask() {
//     for (int i = 0; i < taskSucced->size(); i++) {
//         std::cout << i << ") " << (*mainData)[i] << "\n";
//     }
//     std::cout << "Tugas mana yang mau di edit: ";
//     int editTugas;
//     if (!(std::cin >> editTugas)) {
//         std::cout << "Input tidak valid, jangan gunakan karakter atau
//         kata-kata unik!"; std::cin.clear();
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//     }
//     else {
//         if (editTugas >= 0 && editTugas < taskSucced->size()) {
//             std::cout << "Edit tugas: ";
//             std::cin >> (*taskSucced)[editTugas];
//             std::cout << "Memproses tugas yang di edit...\n";
//             std::this_thread::sleep_for(std::chrono::seconds(3));
//             system("cls");
//             for (int i = 0; i < taskSucced->size(); i++) {
//                 std::cout << i << ") " << (*taskSucced)[i] << "\n";
//             }
//         }
//         else {
//             std::cout << ("Nomor tugas invalid");
//         }
//     }
// }
