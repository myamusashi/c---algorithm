#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {

    cout << "MAGIC 8-BALL: ";

    // Random number 
    srand(time(NULL));
    int answer = rand() % 11;
    cout << answer << " ";

    // else if statement
    if (answer == 0) {
        cout << "Sudah pasti";
    } else if(answer == 1) {
        cout << "Sudah di takdirkan";
    } else if(answer == 2) {
        cout << "Tidak salah lagi";
    } else if(answer == 3) {
        cout << "Sangat yakin";
    } else if(answer == 4) {
        cout << "Kamu akan bergantung dengannya";
    } else if(answer == 5) {
        cout << "Sesuai yang saya liat, ya";
    } else if(answer == 6) {
        cout << "Kemungkinan besar";
    } else if(answer == 7) {
        cout << "Terlihat bagus";
    } else if(answer == 8) {
        cout << "Yes";
    } else if(answer == 9) {
        cout << "Menunjukan tanda iya";
    } else if(answer == 10) {
        cout << "Lebih baik tidak diberitahu saja";
    } else {
        cout << "Sangat di ragukan";
    }

}