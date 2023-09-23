#include <iostream>
#include <string>
#include <vector>

int main(int argc, const char** argv) {
    std::string daftar_tugas_baru;
    std::vector<std::string> daftar_tugas, daftar_tugas_mengerjakan, daftar_tugas_selesai;
    char pilihan;
    char ulang;
    
    system("cls");
    // Task list
    daftar_tugas[0] = "1) Tugas matematika";
    daftar_tugas[1] = "2) Tugas Fisika dasar";
    daftar_tugas[2] = "3) Tugas logika pemrograman"; 
    daftar_tugas[3] = "4) Tugas bahasa indonesia";
    daftar_tugas[4] = "5) Tugas Basic english";
    daftar_tugas[5] = "6) Tugas PJOK";
    daftar_tugas[6] = "7) Tugas Pendidikan pancasila";
    daftar_tugas[7] = "8) Tugas agama";
    daftar_tugas[8] = "9) Tugas project kelompok";
    daftar_tugas[9] = "10) Tugas english TOEFL";


    std::cout<<"\t\t\t***********************************************************************" << std::endl;
	std::cout<<"\t\t\t                       Pengelolaan Daftar Tugas                        " << std::endl;
    std::cout<<"\t\t\t***********************************************************************\n\n" << std::endl;
    // Looping
    do
    {
        std::cout << "Menu Utama\n" << std::endl;
        std::cout << "Apa yang mau anda lakukan: " << std::endl;
        std::cout << "1) Mau membuat list tugas baru\n";
        std::cout << "2) Mau menampilkan tugas sekarang\n";
        std::cout << "3) Mau menandai tugas\n";
        std::cout << "4) Keluar dari program\n\n";
        std::cout << "Pilih menu yang mau anda lakukan(1-4): ";
        std::cin >> pilihan;

        switch (pilihan) {
            case '1':
                std::cout << "Anda memilih: Tambah tugas" << std::endl;
                // Logic for add task
                std::cout << "Tugas apa yang mau anda tambahkan? ";
                std::cin.ignore(); // Clean buffer input
                std::getline(std::cin, daftar_tugas_baru); 
                daftar_tugas.push_back(daftar_tugas_baru); // Add to vector
                std::cout << "Tugas: " << daftar_tugas_baru << std::endl;
                break;
            case '2': 
                std::cout << "Anda memilih: Tampilkan tugas" << std::endl;
                // Logic for view task
                for (int i = 0; i < daftar_tugas.size(); i++) {
                    std::cout << (i + 1) << ". " << daftar_tugas[i] << std::endl;
                }
                break;
            case '3':
                std::cout << "Anda memilih: Tandai tugas selesai" << std::endl;
                // Logic for check the task
                break;
            case '4':
                std::cout << "Anda memilih: Keluar" << std::endl;
                break;
            default:
                std::cout << "Pilihan tidak valid. Silakan coba lagi." << std::endl;
                break;
            }
            std::cout << std::endl;
            std::cout << "Ingin memilih menu lain(y/n)? ";
            std::cin >> ulang;
    
    } while (ulang != 'n');
    std::cout << "\nterima kasih sudah menggunakan program ini";
    return 0;
    
}


