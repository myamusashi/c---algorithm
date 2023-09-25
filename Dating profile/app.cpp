// main.cpp
#include <iostream>
#include "profile.h"

int main() {
    std::vector<std::string> hobbies = {"Reading", "Gaming"};
    Profile obj("John", 25, "New York", "USA", hobbies);

    // Menampilkan profil
    std::string profileInfo = obj.view_profile();
    std::cout << profileInfo;

    // Menambahkan hobi
    obj.add_hobby("Hiking");

    // Menampilkan profil lagi
    profileInfo = obj.view_profile();
    std::cout << "Updated Profile:\n" << profileInfo;

    return 0;
}





