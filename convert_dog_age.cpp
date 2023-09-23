#include <iostream>

int main() {

  //variable int dog and human age
    std::string dog = "San";s //dog name
    int dog_age = 2; // dog age 
    int early_years = 21; // human age
    int later_years; // define calculation
    int human_years; // result calculation
// PS: you can make this code more simple like "int early_years, later_years, human_years"


  // calculate dog years to human age
    later_years = (dog_age - 2) * 4; //dog age decrease by 2 and times 4
    human_years = early_years + later_years; // final calculation

  // print dog years 
    std::cout << "My name is " << dog << " ruff ruff, I am " << human_years << " years old in human years"; // final result with print after calculations
}