#ifndef PROFILE_H
#define PROFILE_H

#include <string>
#include <vector>

class Profile {
private:
    std::string name, city, country;
    std::vector<std::string> hobbies;
    int age;

public:
    Profile(std::string new_name, int new_age, std::string new_city, std::string new_country, std::vector<std::string> new_hobbies);

    std::string view_profile();
    void add_hobby(std::string new_hobby);
};

#endif