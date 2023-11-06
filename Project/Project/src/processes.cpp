#include "../headers/processes.h"

#include <boost/algorithm/string.hpp>
#include <bsoncxx/json.hpp>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>

#include "bsoncxx/builder/basic/document.hpp"
#include "bsoncxx/builder/basic/kvp.hpp"

using namespace bsoncxx;

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;

SourceData::SourceData(const std::string &conn, const std::string &dbs,
                       const std::string &taskqueue,
                       const std::string &taskstodo,
                       const std::string &finishedtasks)
    : connection_(mongocxx::uri(conn)),
      database_(connection_[dbs]),
      newTasks_(database_[taskqueue]),
      inProgress_(database_[taskstodo]),
      completedTask_(database_[finishedtasks]) {
  // Doing something here, if necessary
}

void SourceData::AddTask() 
{
  std::string task, subject, dosen, category;
  const int max_length = 50;  // batas maksimal panjang input

  std::cout << "Nama tugas: ";
  std::cin.ignore();
  std::getline(std::cin, task);     // baca input sebagai string
  while (task.size() > max_length)  // periksa panjang string
  {
    std::cout << "Input terlalu panjang, maksimal 50 karakter.\n";
    std::cout << "Nama tugas: ";
    std::getline(std::cin, task);  // baca input lagi
  }
  boost::algorithm::trim(task);
  std::cout << "\nMata pelajaran: ";
  std::getline(std::cin, subject);     // baca input sebagai string
  while (subject.size() > max_length)  // periksa panjang string
  {
    std::cout << "Input terlalu panjang, maksimal 50 karakter.\n";
    std::cout << "Mata pelajaran: ";
    std::getline(std::cin, subject);  // baca input lagi
  }
  boost::algorithm::trim(subject);

  std::cout << "\nDosen pengajar: ";
  std::getline(std::cin, dosen);     // baca input sebagai string
  while (dosen.size() > max_length)  // periksa panjang string
  {
    std::cout << "Input terlalu panjang, maksimal 50 karakter.\n";
    std::cout << "Dosen pengajar: ";
    std::getline(std::cin, dosen);  // baca input lagi
  }
  boost::algorithm::trim(dosen);

  std::cout << "\nKategori pelajaran (wajib/tambahan): ";
  std::getline(std::cin, category);     // baca input sebagai string
  while (category.size() > max_length)  // periksa panjang string
  {
    std::cout << "Input terlalu panjang, maksimal 50 karakter.\n";
    std::cout << "Kategori pelajaran (wajib/tambahan): ";
    std::getline(std::cin, category);  // baca input lagi
  }
  boost::algorithm::trim(category);

  std::cout << "Memproses tugas baru...\n";

  // Assume that task, subject, dosen, category are strings
  auto add_doc = make_document(
      kvp("task", task), kvp("subject", subject),
      kvp("dosen", dosen), kvp("category", category), kvp("completed", false));
  // Use insert_one to insert a single document
  auto insert_doc = add_doc.view();
  newTasks_.insert_one(insert_doc);

  for (auto &&element : insert_doc) {
    if (element.type() == bsoncxx::type::k_int32) {
      std::cout << element.key() << ": "
                << element.get_int32().value << "\n";
    }
    if (element.type() == bsoncxx::type::k_utf8) {
      std::cout << element.key() << ": "
                << element.get_string().value.to_string() << "\n";
    } 
    if (element.type() == bsoncxx::type::k_bool) {
      bool bool_value = element.get_bool().value;
      std::string bool_str = bool_value ? "sudah" : "belum";
      std::cout << element.key() << ": " << bool_str << "\n";
    }
  }
}

// void SourceData::TasktoDo() {
//     /*
//     Cara kode ini bekerja, data array yang dipilih untuk selesai akan di
//     hapus di function mainData dan akan dipindahkan ke toDo yang ada di file
//     source_data.h
//     */
//     std::string taskWork;

//     auto cursor_all = newTasks_.find({});
//     for (auto&& doc : cursor_all) {
//     // Do something with doc
//       if (doc.type() == bsoncxx::type::k_utf8) {
//         std::cout << doc.key() << ": " element.get_string().value.to_string()
//         << "\n";
//       }
//     }
//     std::cout << "Tugas yang mau dikerjakan: ";
//     int nomorTugasDikerjakan;

//     // Menangani input pengguna yang tidak valid dengan instruksi if
//     if (!(std::cin >> nomorTugasDikerjakan)) {
//         std::cout << "Input tidak valid. Harap masukkan nomor tugas yang
//         valid." << "\n"; std::cin.clear(); // Clean buffer input
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//     }
//     else {
//         if (nomorTugasDikerjakan >= 0 && nomorTugasDikerjakan <
//         mainData->size()) {
//             taskWork = (*mainData)[nomorTugasDikerjakan];

//             mainData->erase(mainData->begin() + nomorTugasDikerjakan);
//             toDo->push_back(taskWork);
//             std::cout << "Memproses tugas yang akan dikerjakan...\n";
//             std::this_thread::sleep_for(std::chrono::seconds(3));
//             system("cls");
//             std::cout << "Tugas " << taskWork << " akan dikerjakan" << "\n";
//         }
//         else {
//             std::cout << ("Nomor tugas tidak valid");
//         }
//     }
// }

// void SourceData::CompletedTask() {
//     /*
//     Cara kode ini bekerja, data array yang dipilih untuk selesai akan di
//     hapus di function mainData dan akan dipindahkan ke taskSucced
//     */
//     std::string completed_task;

//     for (int i = 0; i < toDo->size(); i++) {
//         std::cout << i << ") " << (*toDo)[i] << "\n";
//     }
//     std::cout << "Tugas yang sudah selesai: ";
//     int nomorTugasSelesai;
//     // Menangani input pengguna yang tidak valid dengan instruksi if
//     if (!(std::cin >> nomorTugasSelesai)) {
//         std::cout << "Input tidak valid. Harap masukkan nomor tugas yang
//         valid." << "\n"; std::cin.clear(); // Clean buffer input
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//     }
//     else {
//         if (nomorTugasSelesai >= 0 && nomorTugasSelesai < toDo->size()) {
//             completed_task = (*toDo)[nomorTugasSelesai];

//             toDo->erase(toDo->begin() + nomorTugasSelesai);
//             taskSucced->push_back(completed_task);
//             std::cout << "Memproses tugas selesai...\n";
//             std::this_thread::sleep_for(std::chrono::seconds(3));
//             system("cls");
//             std::cout << "Tugas " << completed_task << " telah selesai" <<
//             "\n";
//         }
//         else {
//             std::cout << ("Nomor tugas tidak valid");
//         }
//     }
// }

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
