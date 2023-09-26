#include <iostream>

int main() {
    std::string pilihan;
    double kecepatan, jarak, waktu;
    double v, s, t;

    std::cout << "1) Hitung kecepatan" << std::endl;
    std::cout << "2) Hitung jarak" << std::endl;
    std::cout << "3) Hitung waktu" << std::endl;
    std::cout << "mau hitung yang mana: ";
    std::cin >> pilihan;
        if (pilihan == "1")
        {  
            std::cout << "Masukkan jarak: ";
            std::cin >> s;
            std::cout << "Masukkan waktu: ";
            std::cin >> t;
            v = s / t; // kecepatan = jarak / waktu
            std::cout << "hasilnya: " << v << std::endl;
        } else if (pilihan == "2")  
        {
            std::cout << "Masukkan kecepatan: ";
            std::cin >> v;
            std::cout << "Masukkan waktu: ";
            std::cin >> t;
            s = v * t; // jarak = kecepatan * waktu
            std::cout << "Hasilnya: " << s << std::endl;
        } else if (pilihan == "3") 
        {
            std::cout << "Masukkan kecepatan: ";
            std::cin >> v;
            std::cout << "Masukkan jarak: ";
            std::cin >> s;
            t = s / v; // waktu = jarak / kecepatan
            std::cout << "Hasilnya: " << t << std::endl;
        } else {
            std::cout << "Pilihan tidak tersedia" << std::endl;
        }
    return 0;
}