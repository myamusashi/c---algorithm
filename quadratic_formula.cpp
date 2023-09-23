#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double a, b, c; // Variable desimal
    double root1, root2; // Variable akar

    cout << "Enter a: ";
    cin >> a;
    cout << "Enter b: ";
    cin >> b;
    cout << "Enter c: ";
    cin >> c;

    // Penjumlahan akar
    root1 = (-b + std::sqrt(b*b - 4 * a * c)) / (2 * a);
    root2 = (-b - std::sqrt(b*b - 4 * a * c)) / (2 * a);

    // Hasil akhir penjumlahan
    cout << "hasil dari root 1: " << root1 << "\n";
    cout << "hasil dari root 2: " << root2 << "\n";
}