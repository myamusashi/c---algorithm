#include <iostream>
using namespace std;

int main() {
  
  int kg, badan_pria_ideal, badan_wanita_ideal;
  double cm;
  std::string jenis_kelamin;
  
  cout << "INPUT BERAT BADAN: ";
  cin >> kg;
  cout << "INPUT TINGGI BADAN: ";
  cin >> cm;
  cout << "INPUT JENIS KELAMIN(pria/wanita): ";
  cin >> jenis_kelamin;
  
  if (jenis_kelamin == "pria") {
     badan_pria_ideal = (cm - 100) - (cm - 100) * 0.1; // 10% = 0.1
     cout << "\n\tKesimpulan hasil ini" << endl;
     cout << "Berat: " << kg << "\nTinggi: " << cm << "\nBerat ideal: " << badan_pria_ideal << "\nJenis kelamin: " << jenis_kelamin << "\n"<< endl;
     
  } else if (jenis_kelamin == "wanita") {
     badan_wanita_ideal = (cm - 100) - (cm - 100) * 0.15; // 15% = 0.15
     cout << "\tKesimpulan hasil ini" << endl;
     cout << "Berat: " << kg << "\nTinggi: " << cm << "\nBerat ideal: " << badan_wanita_ideal<< "\nJenis kelamin: " << jenis_kelamin << "\n"<< endl;
  } else {
     cout << "invalid/typo";
  }
}