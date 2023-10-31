#ifndef CREDENTIALS_H
#define CREDENTIALS_H

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <string>

class CredentialAccess {
  public:
    CredentialAccess(const std::string& conn, const std::string& db, const std::string& coll); 


    void ProcessRegister(); 
    void LoginProgram();
  private:
    mongocxx::instance start;
    mongocxx::client connection_;
    mongocxx::database database_;
    mongocxx::collection collection_;
};

#endif
