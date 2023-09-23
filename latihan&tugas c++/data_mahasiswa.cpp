#include <iostream>
#include <string>


int main(int argc, const char** argv) {
    std::string nama_mahasiswa, alamat, e_mail, telepon;
    system("cls ");

    // Input data diri
    std::cout << "Masukkan nama anda: ";
    std::cin >> nama_mahasiswa;
    std::cout << "Masukkan alamat anda: ";
    std::cin >> alamat;
    std::cout << "Masukkan e-mail anda: ";
    std::cin >> e_mail;
    std::cout << "Masukkan telepon anda: ";
    std::cin >> telepon;

    // Menampilkan data diri yang sudah di input
    std::cout << "Nama: " << nama_mahasiswa << "\n" << "alamat anda: " << alamat << "\n" << "e-mail anda: " << e_mail << "\n" << "nomor telepon anda: " << telepon << std::endl;
    return 0;
}