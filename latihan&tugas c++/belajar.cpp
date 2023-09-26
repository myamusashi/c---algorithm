#include <iostream>
#include <string>
#include <vector>

int main() {
    
    std::string username = "gilang", user_verif ;
    int password = 1234, admin_pass = 4321, pass_verif, token_admin;
    
    std::vector<std::string> data_array = { 
        "Nama: Gilang Ramadhan",
        "NIM: 123456789",
        "Jurusan: Teknik Informatika",
        "Fakultas: Teknik",
        "Universitas: Universitas Pamulang"
    };

    std::cout << "Masukkan username: ";
    std::cin >> user_verif;
    std::cout << "Masukkan password: ";
    std::cin >> pass_verif;

    if (user_verif == username && pass_verif == password) {
        std::cout << "Login berhasil" << std::endl;
        std::cout << "Masukkan password admin: ";
        std::cin >> pass_verif;
        token_admin = pass_verif == admin_pass;
        switch (token_admin)
        {
            case 1: 
                std::cout << "\nSelamat anda berhasil mengakases data: \n";
                for (int i = 0; i < data_array.size(); i++)
                {
                 std::cout << data_array[i] << std::endl;   
                }
                break;
        default:
            break;
        }
    } else {
        std::cout << "Login gagal" << std::endl;
    }
    return 0;
}