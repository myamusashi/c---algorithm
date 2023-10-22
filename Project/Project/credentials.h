#pragma once

#include <string>
#include <vector>

class UserPass {
public:
    // Constructor
    UserPass(std::vector<std::string>* id, std::vector<std::string>* access);
  
    const int ProcessRegister();
    void LoginProgram();
private:
    // Data saving
    std::vector<std::string>* username;
    std::vector<std::string>* password;
};