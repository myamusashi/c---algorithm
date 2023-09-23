#include <iostream> 
int main() {

    // variable nama   
    int gryffindor  = 0;
    int hufflepuff  = 0;
    int ravenclaw   = 0;
    int slytherin   = 0;

    // variable untuk mengisi jawaban
    int answer1;
    int answer2;
    int answer3;
    int answer4;

    system("cls"); // Clean console
    std::cout << "\tThe Sorting Hat Quiz\n";
    
    // Pertanyaan 1
    std::cout << "Q1) When i'm dead, i want people to remember me as: \n";
    std::cout << "1) The good\n";
    std::cout << "2) The great\n";
    std::cout << "3) The wise\n";
    std::cout << "4) The Bold\n";

    // Stor jawaban ke variable answer
    std::cin >> answer1;

    // conditional if else untuk pertanyaan di atas 
    if (answer1 == 1) {
        hufflepuff += 1; // Nilai akan bertambah 1 ketika user memilih "1"
    } else if (answer1 == 2) {
        slytherin += 1;
    } else if (answer1 == 3) {
        ravenclaw += 1;
    } else if (answer1 == 4) {
        gryffindor += 1;
    } else {
        std::cout << "Invalid input" << std::endl;
    }

    // Pertanyaan 2
    std::cout << "Q2) Dawn or Dusk" << std::endl;
    std::cout << "1) Dawn" << std::endl;
    std::cout << "2) Dusk" << std::endl;
    std::cin >> answer2;

    if (answer2 == 1) { 
        gryffindor += 1;
        ravenclaw += 1;
    } else if (answer2 == 2) {
        hufflepuff += 1;
        slytherin += 1;
    } else {
        std::cout << "Invalid input";
    }

    // Pertanyaan 3
    std::cout << "Q3) Which kind of instrument most pleases your ears? \n";
    std::cout << "1) The violin\n";
    std::cout << "2) The trumpet\n";
    std::cout << "3) The piano\n";
    std::cout << "4) The drum\n";
    std::cin >> answer3;

    if (answer3 == 1) { 
        slytherin += 1;
    } else if (answer3 == 2) {
        hufflepuff += 2;
    } else if (answer3 == 3) {
        ravenclaw += 3;
    } else if (answer3 == 4) {
        gryffindor += 4;
    } else {
        std::cout << "Invalid input";
    }
    
    // Pertanyaan 4
    std::cout << "Q4) Which road tempts you most? " << std::endl;
    std::cout << "1) The wide, sunny grassy lane" << std::endl;
    std::cout << "2) The narrow, dark, lantern-lit alley" << std::endl;
    std::cout << "3) The twisting, leaf-strewn path through woods" << std::endl;
    std::cout << "4) The cobbled street lined(ancient buildings)" << std::endl;
    std::cin >> answer4;

    if (answer4 == 1) { 
        hufflepuff += 1;
    } else if (answer4 == 2) {
        slytherin += 1;
    } else if (answer4 == 3) {
        gryffindor += 1;
    } else if (answer4 == 4) {
        ravenclaw += 1;
    } else {
        std::cout << "Invalid input" << std::endl;
    }

    std::string house; // Peringkat 1 
    int max = 0; // Variable untuk menandakan nilai paling besar

    if (gryffindor > max) { 
        max = gryffindor;
        house = "gryffindor";
    } else if (hufflepuff > max) {
        max = hufflepuff;
        house = "hufflepuff";
    } else if (ravenclaw > max) {
        max = ravenclaw;
        house = "ravenclaw";
    } else if (slytherin > max) {
        max = slytherin;
        house = "slytherin";
    } else {
        std::cout << "No one else" << std::endl;
    }

    std::cout << house << std::endl;

    return 0;
}