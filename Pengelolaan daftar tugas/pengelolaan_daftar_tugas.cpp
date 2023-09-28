#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> mainData {
   "matematika",
   "Fisika dasar",
   "logika pemrograman",
   "bahasa indonesia",
   "Basic english",
   "PJOK",
   "Pendidikan pancasila",
   "agama",
   "project kelompok",
   "english TOEFL"
};


void addTask(std::string daftar_tugas_baru) {
        std::cout << "Tugas yang mau ditambahkan: ";
        std::cin.ignore();
        std::getline(std::cin, daftar_tugas_baru);
        mainData.push_back(daftar_tugas_baru);
        std::cout << "Tugas baru: " << daftar_tugas_baru << std::endl;
}

std::vector<std::string> tugasSelesai {
    // I N V I S I B L E D A T A

};
        
void CompletedTask(std::string completed_task) {
        for (int i = 0; i < mainData.size(); i++)
        {
            std::cout << i << ") " << mainData[i] << std::endl;
        }
        std::cout << "Tugas yang sudah selesai: ";
        int nomorTugasSelesai;
        std::cin >> nomorTugasSelesai;
        completed_task = mainData[nomorTugasSelesai];
        mainData.erase(mainData.begin() + nomorTugasSelesai);
        tugasSelesai.push_back(completed_task);
        std::cout << "Tugas " << completed_task << " telah selesai" << std::endl;
}

void viewTask() {
    for (int i = 0; i < mainData.size(); i++) {
        std::cout << i << ") " << mainData[i] << std::endl;
    }
}

void viewFinishTask() {
    for (int i = 0; i < tugasSelesai.size(); i++)
    {
        std::cout << i << ") " << tugasSelesai[i] << std::endl;
    }    
}

void removeTask(std::string tugasHapus) {
        for (int i = 0; i < mainData.size(); i++)
        {
            std::cout << i << ") " << mainData[i] << std::endl;
        }
        std::cout << "Tugas mana yang mau dihapus";
        int nomor_tugas;
        std::cin >> nomor_tugas;
        tugasHapus = mainData[nomor_tugas];
        mainData.erase(mainData.begin() + nomor_tugas);
        std::cout << "Tugas " << tugasHapus << " Telah dihapus" << std::endl;
}

void editTask(int editTugas) {
/* 
Fungsi "editTugas" adalah mengambil input int 
untuk meminta nomor yang dipilih untuk di edit dan mengecek 
apakah tugas yang diedit ada di mainData jika ada, maka menunggu 
user memasukkan string baru untuk menggantikan tugas yang lama 
dan memperlihatkan tugas yang sudah di edit (feature paling nyusahin)
*/
    for (int i = 0; i < mainData.size(); i++)
    {
        std::cout << i << ") " << mainData[i] << std::endl;
    }
    std::cout << "Tugas mana yang mau di edit: ";
    std::cin >> editTugas;
    if (editTugas >= 0 && editTugas < mainData.size())
    {
        std::cout << "Edit tugas: ";
        std::cout << "\n";
        std::cin >> mainData[editTugas];
        for (int i = 0; i < mainData.size(); i++)
        {
            std::cout << i << ") " << mainData[i] << std::endl;
        }
    } else {
        std::cout << "Nomor tugas invalid" << std::endl;
    }
}

int main(int argc, const char** argv) {
    std::string user_verification;
    int pass_verification;
    char pilihan;
    char ulang;

    // call variable  
    std::vector<std::string> tugas(10); 
    std::string tugas_baru, hapus_tugas, tugas_selesai; 
    int editTugas;

    system("cls");
    std::cout << "\t\t\t***********************************************************************"<< std::endl;
    std::cout << "\t\t\t                       Pengelolaan Daftar Tugas                        "<< std::endl;
    std::cout << "\t\t\t***********************************************************************\n\n"<< std::endl;
    // Login 
    // std::cout << "Login ke program: ";
    // std::cin >> user_verification;
    // std::cout << "Masukkan password: ";
    // std::cin >> pass_verification;
    // if (user_verification == username && pass_verification == password) { 
    do {
        std::cout << "Lanjut\n";
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
                addTask(tugas_baru);
                break;
                case '2':
                CompletedTask(tugas_selesai);
                break;
                case '3':
                viewTask();
                break;
                case '4':
                viewFinishTask();
                break;
                case '5':
                removeTask(hapus_tugas);
                break;
                case '6':
                editTask(editTugas);
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
    } while(ulang != 'n');
    // } else {
    
    // }
    return 0;
}