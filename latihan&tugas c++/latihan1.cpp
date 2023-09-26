#include <iostream>

int main() {
    std::string nama = "Saya", user;
    int pass_verification, password = 1234, pass;

    std::cout << "Masukkan username: ";
    std::cin >> user;
    if (nama == user) {
        std::cout << "Masukkan password: ";
        std::cin >> pass_verification;
        pass = pass_verification == password;
        switch (pass)
        {
            case 1: 
                std::cout << "Halaman admin" << std::endl;
                nama = "admin";
                break;
        default:
            break;
        }
    } else {
        std::cout << "Anda bukan admin" << std::endl;
    }
    std::cout << "Yang masuk " << nama << std::endl;
}