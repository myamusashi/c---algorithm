#include <iostream>
#include <string>
#include <vector>

int main() {
  std::string user_verification, username = "Admin";
  int password = 1234, pass_verification;
  std::vector<std::string> daftar_tugas_selesai, daftar_tugas(10);
  std::string daftar_tugas_baru;
  char pilihan;
  char ulang;

  daftar_tugas[0] = "Tugas matematika";
  daftar_tugas[1] = "Tugas Fisika dasar";
  daftar_tugas[2] = "Tugas logika pemrograman";
  daftar_tugas[3] = "Tugas bahasa indonesia";
  daftar_tugas[4] = "Tugas Basic english";
  daftar_tugas[5] = "Tugas PJOK";
  daftar_tugas[6] = "Tugas Pendidikan pancasila";
  daftar_tugas[7] = "Tugas agama";
  daftar_tugas[8] = "Tugas project kelompok";
  daftar_tugas[9] = "Tugas english TOEFL";
  
  system("cls");
  std::cout << "\t\t\t***********************************************************************"<< std::endl;
  std::cout << "\t\t\t                       Pengelolaan Daftar Tugas                        "<< std::endl;
  std::cout << "\t\t\t***********************************************************************\n\n"<< std::endl;
  // Login 
  std::cout << "Login ke program: ";
  std::cin >> user_verification;
  std::cout << "Masukkan password: ";
  std::cin >> pass_verification;
  if (user_verification == username && pass_verification == password)
{
  // Looping
  do {

    // Setiap selesai menjalankan suatu perintah diharuskan login lagi
    
      std::cout << "Lanjut\n";
            std::cout << "Menu Utama\n" << std::endl;
            std::cout << "Apa yang mau anda lakukan: " << std::endl;
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
            case '1': {
              std::cout << "Anda memilih: Tambah tugas" << std::endl;
              // Logic menambah tugas
              std::cout << "Tugas apa yang mau anda tambahkan? ";
              std::cin.ignore(); // Membersihkan buffer input
              std::getline(std::cin, daftar_tugas_baru);
              daftar_tugas.push_back(daftar_tugas_baru); // Menambahkan tugas ke vektor
              std::cout << "Tugas: " << daftar_tugas_baru << std::endl;
              break;
            }
            case '2': {
              std::cout << "Anda memilih: Tandai tugas selesai" << std::endl;
              // Logic tandai tugas "selesai"
              std::cout << "Tugas mana yang sudah selesai? ";
              for (int i = 0; i < daftar_tugas.size(); i++) { // size() = melihat berapa banyak jumlah array di dalam daftar_tugas
                std::cout << i << ")" << daftar_tugas[i] << std::endl;
              }
              // Ambil nomor dari daftar_tugas
              int nomor_tugas_selesai;
              std::cin >> nomor_tugas_selesai;
              std::string completed_task = daftar_tugas[nomor_tugas_selesai]; 
              daftar_tugas.erase(daftar_tugas.begin() + nomor_tugas_selesai); // Hapus tugas yang udah selesai dari daftar_tugas
              // Memindahkan tugas yang sudah selesai ke vector daftar_tugas_selesai
              daftar_tugas_selesai.push_back(completed_task);
              std::cout << "Tugas " << completed_task << " telah ditandai selesai." << std::endl;
              break;
            }
            case '3': {
              std::cout << "Anda memilih: Tampilkan tugas" << std::endl;
              // Logic melihat tugas
              for (int i = 0; i < daftar_tugas.size(); i++) { 
                std::cout << i << ") " << daftar_tugas[i] << std::endl;
              }
              break;
            }
            case '4': {
              std::cout << "Anda memilih: Tampilkan tugas yang sudah selesai" << std::endl;
              for (const auto& tugas : daftar_tugas_selesai) {
                for (int i = 0; i < daftar_tugas_selesai.size(); i++)
                {
                  std::cout << i << ")" << tugas << std::endl;
                }
              }
              }
              break;
            case '5': {
              std::cout << "Anda memilih: Menghapus tugas" << std::endl;
              // Logic menghapus tugas
              std::cout << "Tugas mana yang mau anda hapus? ";
              for (int i = 0; i < daftar_tugas.size(); i++) {
                std::cout << i << ")" << daftar_tugas[i] << std::endl;
              }
              // Logika dihapus sama dengan logika menandai
              int nomor_tugas_dihapus;
              std::cin >> nomor_tugas_dihapus;
              std::string deleted_task = daftar_tugas[nomor_tugas_dihapus];
              daftar_tugas.erase(daftar_tugas.begin() + nomor_tugas_dihapus);
              std::cout << "Tugas " << deleted_task << " telah dihapus." << std::endl;
              break;
            }
            case '6': {
              std::cout << "Anda memilih: edit tugas" << std::endl;
              // Logic edit tugas
              // Masih maintance
              for (int i = 0; i < daftar_tugas.size(); i++) {
                std::cout << i << ")" << daftar_tugas[i] << std::endl;
              }
              int nomor_tugas_diedit;
              std::cout << "Tugas mana yang mau anda edit? "; 
              std::cin >> nomor_tugas_diedit;
              /* 
              Fungsi "nomor_tugas_diedit" adalah mengambil tipe data int 
              untuk meminta nomor yang dipilih untuk di edit dan mengecek 
              apakah tugas yang diedit ada di daftar_tugas jika ada, maka menunggu 
              user memasukkan string baru untuk menggantikan tugas yang 
              lama dan memperlihatkan tugas yang sudah di edit (feature paling nyusahin)
              */
              if (nomor_tugas_diedit >= 0 && nomor_tugas_diedit < daftar_tugas.size())
              {
                std::cout << "Edit tugas: ";
                std::cin >> daftar_tugas[nomor_tugas_diedit];
                for (int i = 0; i < daftar_tugas.size(); i++)
                {
                  std::cout << i << ")" << daftar_tugas[i] << std::endl;
                }
              } else
              {
                std::cout << "Tugas tidak ditemukan" << std::endl;
              }
              break;
            }
            case '7': {
              std::cout << "Anda memilih: Keluar" << std::endl;
              std::cout << "Terima kasih sudah menggunakan program ini" << std::endl;
              return 0;
            }
            default: {
              std::cout << "Pilihan tidak valid. Silakan coba lagi." << std::endl;
              break;
            }
            }
            std::cout << std::endl;
            std::cout << "Ingin memilih menu lain(y/n)? ";
            std::cin >> ulang;
        
          } while (ulang != 'n');
            std::cout << "\nterima kasih sudah menggunakan program ini";
          } else {
            return 0;
          }  
  return 0;      
}
 