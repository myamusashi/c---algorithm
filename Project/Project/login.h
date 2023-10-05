#include <string>
#include <vector>

#ifndef LOGIN_H
#define LOGIN_H

class UserPass {
public:
    // Constructor
    UserPass(std::vector<std::string>* id, std::vector<std::string>* access);
  
    void ProcessRegister();
    void LoginProgram();
private:
    // Data saving
    std::vector<std::string>* username;
    std::vector<std::string>* password;
};
#endif