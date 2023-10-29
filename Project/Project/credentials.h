#pragma once

#include <mongocxx/v_noabi/mongocxx/client.hpp>
#include <mongocxx/v_noabi/mongocxx/instance.hpp>
#include <mongocxx/v_noabi/mongocxx/uri.hpp>
#include <bsoncxx/builder/stream/document.hpp>

#include <openssl/sha.h>
#include <openssl/evp.h> 

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <regex>

using namespace mongocxx;
using bsoncxx::builder::basic::make_document;
using bsoncxx::builder::basic::kvp;

class MyClass 
{
public:
    MyClass ();
    ~MyClass ();

private:

};

MyClass ::MyClass () 
{

}


MyClass ::~MyClass () 
{

}

// Fungsi untuk mendapatkan password dengan input tersembunyi di Windows
std::string getpass(std::string prompt) {
    std::string password;
    char ch;
    struct termios old_term, new_term;

    std::cout << prompt;
    fflush(stdout);

    // Menyembunyikan input
    tcgetattr(STDIN_FILENO, &old_term);
    new_term = old_term;
    new_term.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);

    while (1) {
        ch = getchar();
        if (ch == '\n') {
            std::cout << std::endl;
            break;
        } else if (ch == 127) { // 127 adalah kode ASCII untuk tombol Backspace
            if (!password.empty()) {
                std::cout << "\b \b"; // Menghapus karakter terakhir dari tampilan
                password.pop_back(); // Menghapus karakter terakhir dari password
            }
        } else {
            std::cout << '*'; // Menampilkan karakter '*' sebagai pengganti
            password.push_back(ch); // Menambahkan karakter ke password
        }
    }

    // Mengembalikan pengaturan terminal asli
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);

    return password;
}

/*----------------------------HASHING PASSWORD----------------------------------------------*/

std::string HashPassword(const std::string& password) 
{
    EVP_MD_CTX* ctx = EVP_MD_CTX_new(); // Buat sebuah konteks untuk hashing.
    EVP_DigestInit_ex(ctx, EVP_sha256(), NULL); // Initialize ctx dengan SHA256 algorithm.
    EVP_DigestUpdate(ctx, password.c_str(), password.length()); // Update ctx dengan password.
    unsigned char md[SHA256_DIGEST_LENGTH]; // deklarasi array untuk di taruh ke store dan outputnya ke hash.
    unsigned int md_len; // deklarasi sebuah variable ke store yang berisi panjang dari hash.
    EVP_DigestFinal_ex(ctx, md, &md_len); //  Finalisasi ctx dan store hash di dalam output array.
    EVP_MD_CTX_free(ctx); // Delete ctx.

    // Ubah hash menjadi hexadecimal string
    std::string hashedPassword;
    for (int i = 0; i < md_len; i++) {
        char hex[3];
        snprintf(hex, 3, "%02x", md[i]);
        hashedPassword += hex;
    }
    return hashedPassword;
}

/*----------------------------VERIFICATION ACCOUNT----------------------------------------------*/
bool VerifyUser(const std::string& username, const std::string& inputPassword, mongocxx::collection& coll) {
    // Query database untuk mengambil hashed password dan username yang diberikan
    bsoncxx::document::value query_docUser = bsoncxx::builder::stream::document{} << "username" << username << bsoncxx::builder::stream::finalize;
    mongocxx::cursor cursorUser = coll.find(query_docUser.view());

    std::string storedHashedPassword;

    for (auto&& docUser : cursorUser) {
        for (const bsoncxx::document::element& elementUser : docUser) {
            if (elementUser.key() == core::v1::string_view("password") && elementUser.type() == bsoncxx::type::k_utf8) {
                storedHashedPassword = elementUser.get_string().value.to_string();
            }
        }
    }

    if (storedHashedPassword.empty()) {
        // Username tidak ada di database
        std::cout << "Username Tidak ada di database" << std::endl;
        return false;
    }

    std::string hashedInputPassword = HashPassword(inputPassword);

    return hashedInputPassword == storedHashedPassword;
}

/*----------------------------ENVIRONMENT VARIABLE----------------------------------------------*/
std::string getEnvironmentVariable(const std::string& environmentVarKey) {
    const char* envValue = std::getenv(environmentVarKey.c_str());
    
    if (envValue != nullptr) {
        std::string environmentVarValue(envValue);
        return environmentVarValue;
    } else {
        std::cerr << "Environment variable MONGODB_URI is not set.";
        return "";
    }
}
auto mongoURIStr = getEnvironmentVariable("MONGODB_URI");
static const mongocxx::uri mongoURI = mongocxx::uri{ mongoURIStr };
/*----------------------------REGISTRATION & LOGIN----------------------------------------------*/
void ProcessRegister() 
{
    // Start Instance mongodb
    options::client client_options;
    auto api = mongocxx::options::server_api{ mongocxx::options::server_api::version::k_version_1 };
    client_options.server_api_opts(api);
    client conn{ mongoURI, client_options };
    database db = conn["datamain"];
    collection coll = db["account"];

    std::string back_auth;
    char back;

    do 
    {
        std::cout << "\033[2J\033[1;1H";
        std::cout << "\t\t\tHalaman registrasi user baru\n";
        std::string user_input; std::cout << "Masukkan username anda: ";
        std::cin >> user_input;

        std::regex userRegex("^(?=.*[A-Za-z].*\\d)[A-Za-z\\d]{8,}$"); // Minimal 8 karakter dengan 1 angka
        bool user_valid = std::regex_match(user_input, userRegex);

        if (user_valid) 
        {
            std::string pass_input = getpass("Masukkan password anda: ");
            std::regex passRegex("^(?=.*[A-Za-z].*\\d)[A-Za-z\\d]{8,}$"); // Minimal 8 karakter dengan 1 huruf besar dan 1 angka
            if (std::regex_match(pass_input, passRegex)) {
                std::string hashedpassword = HashPassword(pass_input);

                bsoncxx::builder::basic::document filter_builder;
                filter_builder.append(kvp("username", user_input), kvp("password", hashedpassword));

                auto result = filter_builder.view();
                coll.insert_one(result);
                std::cout << "Username dan password valid, akun telah terdaftar.\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));

                do 
                {
                    std::cout << "\033[2J\033[1;1H";
                    std::cout << "Login ke akun anda\n";

                    std::string user_verification; std::cout << "Username anda: ";
                    std::cin >> user_verification;

                    std::string pass_verification = getpass("Password anda: ");

                    bool isVerified = VerifyUser(user_verification, pass_verification, coll);
                    std::cout << "verifikasi account...\n";
                    std::this_thread::sleep_for(std::chrono::seconds(2));

                    if (isVerified) 
                    {
                        std::cout << "\033[2J\033[1;1H";
                        std::cout << "Verifikasi berhasil." << std::endl;
                        std::cout << "Masuk program..." << std::endl;
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        break;
                    }
                    else 
                    {
                        std::cout << "\033[2J\033[1;1H";
                        std::cout << "Verifikasi gagal, username atau password tidak cocok." << std::endl;
                        std::this_thread::sleep_for(std::chrono::seconds(2));
                    }
                    std::cout << "Login kembali? (y/n)";
                    std::cin >> back_auth;
                    if (back_auth == "n" || back_auth == "N") 
                    {
                        exit(66);
                    }
                } while (back_auth == "y" || back_auth == "Y");
            }
            else 
            {
                std::cout << "Password invalid, minimal 8 karakter dan 1 huruf besar dan 1 angka" << std::endl;
            }
        }
        else 
        {
            std::cout << "Username invalid, minimal 8 karakter dan 1 angka" << std::endl;
        }
        std::cout << "Ingin Registrasi kembali? (y/n)? ";
        std::cin >> back;
    } while (back == 'y' || back == 'Y');
}

void LoginProgram() 
{
    options::client client_options;
    auto api = mongocxx::options::server_api{ mongocxx::options::server_api::version::k_version_1 };
    client_options.server_api_opts(api);
    client conn{ mongoURI, client_options };
    database db = conn["datamain"];
    collection coll = db["account"];

    std::string back;
    do 
    {
        std::string user_verification; std::cout << "Username anda: ";
        std::cin >> user_verification;

        std::string pass_verification = getpass("Password anda: ");

        bool isVerified = VerifyUser(user_verification, pass_verification, coll);
        std::cout << "verifikasi account...\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));

        if (isVerified) 
        {
            std::cout << "\033[2J\033[1;1H";
            std::cout << "Verifikasi berhasil." << std::endl;
            std::cout << "Masuk program..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            break;
        }
        else 
        {
            std::cout << "\033[2J\033[1;1H";
            std::cout << "Verifikasi gagal, username atau password tidak cocok." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        std::cout << "Login kembali? (y/n)";
        std::cin >> back;
        if (back == "n" || back == "N") 
        {
            exit(66);
        }
    } while (back == "y" || back == "Y");
}
