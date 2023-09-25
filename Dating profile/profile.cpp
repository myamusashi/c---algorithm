// profile.cpp
#include "profile.h"

Profile::Profile(std::string new_name, int new_age, std::string new_city, std::string new_country, std::vector<std::string> new_hobbies) {
    name = new_name;
    age = new_age;
    city = new_city;
    country = new_country;
    hobbies = new_hobbies;
}

std::string Profile::view_profile() {
    std::string profile = "Name: " + name + "\n";
    profile += "Age: " + std::to_string(age) + "\n";
    profile += "City: " + city + "\n";
    profile += "Country: " + country + "\n";
    profile += "Hobbies:\n";
    for (const std::string& hobby : hobbies) {
        profile += " - " + hobby + "\n";
    }
    return profile;
}

void Profile::add_hobby(std::string new_hobby) {
    hobbies.push_back(new_hobby);
}