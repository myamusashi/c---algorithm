/*
Algoritma PPN
menghitung pajak pertambahan nilai 12.5% dari harga barang
*/

#include <iostream>

int main(int argc, const char** argv) {

    double sepatu = 150000;
    double pajak, total; // Definisi variable
    double barang;

    //TODO
    std::cout << "Masukkan barang: ";
    std::cin >> barang;

    pajak = 0.125 * sepatu;
    barang = sepatu + pajak;

    std::cout << "Harga = " << sepatu << " Pajaknya = " << pajak << std::endl;
    std::cout << "Total = " << barang << std::endl;
    return 0;
}