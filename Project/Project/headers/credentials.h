#pragma once

#include <mongocxx/client.hpp>
#include <string>

class CredentialAccess {
  public:
    CredentialAccess(const std::string& conn, const std::string& db, const std::string& coll); 

    void ProcessRegister(); 
    void LoginProgram();
  private:
    mongocxx::client connection_;
    mongocxx::database database_;
    mongocxx::collection collection_;
};

