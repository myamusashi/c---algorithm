#include <iostream>

int main() {
    double f, c, t;
    std::string c_f;

    system("cls");
    std::cout << "Selamat datang" << std::endl;
    std::cout << "1) Celcius ke fahrenheit" << std::endl;
    std::cout << "2) Fahrenheit ke celcius" << std::endl;
    std::cout << "Mau konversi yang mana: ";
    std::cin >> c_f;
    

    if (c_f == "celcius" || c_f == "1") { 
        std::cout << "Berapa angka yang mau di konversi: ";
        std::cin >> c;
        f = (c * 9/5) + 32;
        std::cout << "fahrenheitnya adalah: " << f << std::endl;
    } else if (c_f == "fahrenheit" || c_f == "2") {
        std::cout << "Berapa angka yang mau di konversi";
        std::cin >> f;
        c = (f - 32) * 5/9;
        std::cout << "Celciusnya adalah: " << c;
    } else {
        std::cout << "Tidak ada" << std::endl;
    }
    return 0;
}