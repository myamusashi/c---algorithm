#include <iostream>

int main() {

    double peso, reai, sole; //mata uang
    double dollar_peso, dollar_reai, dollar_sol;

    std::cout << "Enter number of Colombian Pesos: ";
    std::cin >> peso;
    std::cout << "Enter number of Brazilian reais: ";
    std::cin >> reai;
    std::cout << "Enter number of Peru Soles: ";
    std::cin >> sole;    

    // Currency duit lokal ke USD
    double currency_pesos = 0.00025;
    double currency_reais = 0.0012;
    double currency_soles = 0.00094;

    // perhitungan semua duit lokal ke USD
    dollar_peso = (currency_pesos * peso);
    dollar_reai = (currency_reais * reai);
    dollar_sol = (currency_soles * sole);
    std::cout << "US Dollars: $" << dollar_peso << "\n";
    std::cout << "US Dollars: $" << dollar_reai << "\n";
    std::cout << "US Dollars: $" << dollar_sol << "\n";
}