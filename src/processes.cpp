#include "../libs/processes.hpp"

#include <boost/algorithm/string.hpp>
#include <cstdlib>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <thread>

#include "bsoncxx/builder/basic/document.hpp"
#include "bsoncxx/builder/basic/kvp.hpp"
#include "mongocxx/exception/exception.hpp"
#include "mongocxx/model/delete_one.hpp"
#include "mongocxx/model/update_one.hpp"
#include "mongocxx/model/write.hpp"

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

std::string validateInput(const std::string &prompt, const int max_length) {
    std::string input;
    do {
        // Clear the input buffer before each prompt
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << prompt;
        std::getline(std::cin, input);

        boost::algorithm::trim(input);

        if (input.empty()) {
            std::cout << "Input tidak boleh kosong. Silakan coba lagi.\n";
        } else if (input.size() > max_length) {
            std::cout << "Input terlalu panjang, maksimal " << max_length << " karakter.\n";
        }
    } while (input.empty() || input.size() > max_length);

    return input;
}

void SourceData::AddTask() {
    const int max_length = 150;  // batas maksimal panjang input

    std::string task = validateInput("Nama tugas: ", max_length);
    std::string subject = validateInput("Mata pelajaran: ", max_length);
    std::string dosen = validateInput("Dosen pengajar: ", max_length);
    std::string category = validateInput("Kategori pelajaran (wajib/tambahan): ", max_length);
    std::cout << "Memproses tugas baru...\n";

    // Providing a seed value
    srand((unsigned)time(NULL));

    // Get a random number
    int random = 1000 + (rand() % 5000);

    auto add_doc =
        make_document(kvp("no", random), kvp("task", task), kvp("subject", subject),
                      kvp("dosen", dosen), kvp("category", category), kvp("completed", false));

    auto result = newTasks_.insert_one(add_doc.view());
    for (auto &&element : add_doc) {
        if (result->result().inserted_count() == 1 && element.type() == bsoncxx::type::k_int32) {
            std::cout << "Tugas berhasil ditambahkan\n";
            std::cout << element.key() << ": " << element.get_int32().value << "\n";
        }
    }
}

void view(mongocxx::collection &collection) {
    std::cout << "\033[2J\033[1;1H";
    auto &&cursor = collection.find({});
    try {
        for (auto &&doc : cursor) {
            for (bsoncxx::document::element &element : doc) {
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
        std::cerr << "Terjadi kesalahan memproses tugas" << ex.what();
    }
}

void SourceData::DisplayTask() { view(newTasks_); }

void SourceData::DisplayTaskToDo() { view(inProgress_); }

void SourceData::DisplayCompletedTask() { view(completedTask_); }

void SourceData::TasktoDo() {
    /*
    Cara kode ini bekerja, data array yang dipilih untuk selesai akan di
    hapus di function mainData dan akan dipindahkan ke toDo yang ada di file
    source_data.h
    */
    std::cout << "\033[2J\033[1;1H";
    DisplayTask();
    int id;
    std::cout << "Tugas yang mau dikerjakan (masukkan nomor tugas): ";
    std::cin >> id;

    auto &&find_document = newTasks_.find_one(make_document(kvp("no", id)));
    if (!(find_document)) {
        std::cout << "Document yang anda cari tidak ada disini!\n";
    } else {
        std::cout << "Document anda terdaftar di koleksi kami!\n";
        std::cout << "Memproses document anda ke koleksi inProgress\n";

        auto &&insert = find_document->view();
        inProgress_.insert_one(insert);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        newTasks_.delete_one(make_document(kvp("no", id)));
        std::cout << "Dokumen telah masuk ke inProgress";
    }
}

void SourceData::CompletedTask() {
    /*
    Cara kode ini bekerja, data array yang dipilih untuk selesai akan di
    hapus di function mainData dan akan dipindahkan ke taskSucced
    */
    auto document = make_document(kvp("completed", false));
    auto update_document = make_document(kvp("$set", make_document(kvp("completed", true))));

    std::cout << "\033[2J\033[1;1H";
    DisplayTaskToDo();
    int id;
    std::cout << "Masukkan nomor tugas yang sudah selesai: ";
    std::cin >> id;

    auto &&find_document = inProgress_.find_one(make_document(kvp("no", id)));
    if (!(find_document)) {
        std::cout << "Tugas yang anda cari tidak ada disini!\n";
    } else {
        std::cout << "Tugas terdaftar di data!\n";
        std::cout << "Memproses tugas...\n";

        auto &&insert = find_document->view();
        completedTask_.insert_one(insert);
        // Model untuk memproses update
        mongocxx::model::update_one upsert_op{document.view(), update_document.view()};
        // Set upsert
        upsert_op.upsert(true);
        // Create Bulk
        auto bulk = completedTask_.create_bulk_write();
        // Update
        bulk.append(upsert_op);
        bulk.execute();

        std::this_thread::sleep_for(std::chrono::seconds(1));
        inProgress_.delete_one(insert);
        std::cout << "Tugas anda telah selesai dikerjakan!";
    }
}

void remove(mongocxx::collection &collection) {
    int nomor_tugas;

    view(collection);

    std::cout << "Tugas mana yang mau dihapus: ";
    std::cin >> nomor_tugas;

    auto find_document = collection.find_one(make_document(kvp("no", nomor_tugas)));
    if (!(find_document)) {
        std::cout << "Tugas tidak ada di data anda!\n";
        return;
    } else {
        auto cursor = collection.find(make_document(kvp("no", nomor_tugas)));
        std::cout << "\033[2J\033[1;1H";
        std::cout << "Tugas yang akan dihapus: \n";
        for (auto &&view_doc : cursor) {
            for (bsoncxx::document::element &element : view_doc) {
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
        }
        std::this_thread::sleep_for(std::chrono::seconds(3));
        try {
            mongocxx::model::delete_one delete_document{find_document->view()};
            auto bulk = collection.create_bulk_write();
            bulk.append(delete_document);
            bulk.execute();
            std::cout << "\033[2J\033[1;1H";
            std::cout << "Tugas anda sudah terhapus!";
        } catch (mongocxx::exception &e) {
            std::cout << "Ada yang salah saat penghapusan tugas! Silahkan ulang lagi" << e.what();
        }
    }
}

void SourceData::RemoveTask() { remove(newTasks_); }

void SourceData::RemoveTaskToDo() { remove(inProgress_); }

void SourceData::RemoveFinishTask() { remove(completedTask_); }

void update(mongocxx::collection &collection) {
    std::string nomor_tugas;

    std::cout << "\033[2J\033[1;1H";
    view(collection);

    // Clean buffer input
    std::cin.clear();
    std::cin.ignore();

    std::cout << "Nomor tugas yang akan di edit: ";
    std::getline(std::cin, nomor_tugas);
    int tugas = std::stoi(nomor_tugas);

    auto &&cursor = collection.find_one(make_document(kvp("no", tugas)));
    if (!(cursor)) {
        std::cout << "Nomor tugas yang anda cari tidak ada di data";
    } else {
        const int max_length = 150;
        std::string nama_tugas = validateInput("Nama tugas: ", max_length);
        std::string mata_pelajaran = validateInput("Mata pelajaran: ", max_length);
        std::string dosen = validateInput("Nama Dosen: ", max_length);
        std::string kategori = validateInput("Kategori pelajaran: ", max_length);

        try {
            auto bulk = collection.create_bulk_write();

            bulk.append(mongocxx::model::update_one(
                make_document(kvp("no", tugas)),
                make_document(kvp("$set", make_document(kvp("task", nama_tugas))))));
            bulk.append(mongocxx::model::update_one(
                make_document(kvp("no", tugas)),
                make_document(kvp("$set", make_document(kvp("subject", mata_pelajaran))))));
            bulk.append(mongocxx::model::update_one(
                make_document(kvp("no", tugas)),
                make_document(kvp("$set", make_document(kvp("dosen", dosen))))));
            bulk.append(mongocxx::model::update_one(
                make_document(kvp("no", tugas)),
                make_document(kvp("$set", make_document(kvp("category", kategori))))));
            auto result = bulk.execute();
            if (result->modified_count() == 4) {
                std::cout << "berhasil update tugas";
            } else {
                std::cout << "Gagal update tugas";
            }
        } catch (mongocxx::exception &ex) {
        }
    }
}

void SourceData::EditTask() { update(newTasks_); }

void SourceData::EditTaskTodo() { update(inProgress_); }

void SourceData::EditFinishTask() { update(completedTask_); }
