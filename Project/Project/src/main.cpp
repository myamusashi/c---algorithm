#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include "../headers/credentials.h"
#include "mongocxx/instance.hpp"
#include "mongocxx/uri.hpp"
#include "../headers/processes.h"
/*----------------------------ENVIRONMENT VARIABLE----------------------------------------------*/
std::string getEnvironmentVariable(const std::string &environmentVarKey)
{
    const char *envValue = std::getenv(environmentVarKey.c_str());

    if (envValue != nullptr)
    {
        std::string environmentVarValue(envValue);
        return environmentVarValue;
    }
    else
    {
        std::cerr << "Environment variable MONGODB_URI is not set.";
        return "";
    }
}
auto mongoURIStr = getEnvironmentVariable("MONGODB_URI");
static const mongocxx::uri mongoURI = mongocxx::uri{ mongoURIStr };

int main(int argc, const char **argv)
{
    mongocxx::instance inst{};
    CredentialAccess credentials(mongoURI.to_string(), "authentication", "user_accounts");
    SourceData data(mongoURI.to_string(), "task", "new_task", "task_todo", "finish_task");
    
    std::cout << "\033[2J\033[1;1H";
    std::cout << "\t\t\t\t\t\tLogin\n";
    std::cout << "\t\t\t\t\t\t(1) Login akun\n";
    std::cout << "\t\t\t\t\t\t(2) Registrasi akun\n";
    std::cout << "\t\t\t\t\t\tSilahkan masuk atau daftar akun anda (1/2): ";
    std::string choice;
    std::getline(std::cin, choice);

    try {
        int option = std::stoi(choice);  
        switch (option) { 
            case 1:
                credentials.LoginProgram();
                break;
            case 2:
                credentials.ProcessRegister();
                break;
            default:
                std::cout << "Input tidak valid. Silakan pilih 1 atau 2.\n";
                return 1; 
        }
    } catch (std::invalid_argument& e) {
        std::cout << "Input tidak valid. Silakan pilih 1 atau 2.\n";
        return 1;
    } catch (std::out_of_range& e) {
        std::cout << "Input tidak valid. Silakan pilih 1 atau 2.\n";
        return 1; 
    }

    int pilihan;
    char ulang;

    std::cout << "\033[2J\033[1;1H";
    std::cout << "\t\t\t***********************************************************************" << std::endl;
    std::cout << "\t\t\t                       Pengelolaan Daftar Tugas                        " << std::endl;
    std::cout << "\t\t\t***********************************************************************" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    do
    {
        std::cout << "\033[2J\033[1;1H"; // clear console
        std::cout << "Menu Utama\n\n";
        std::cout << "Apa yang mau anda lakukan\n";
        std::cout << "1) Mau membuat list tugas baru?\n";
        std::cout << "2) Mau menandai tugas yang mau dikerjakan?\n";
        std::cout << "3) Mau menandai tugas selesai?\n";
        std::cout << "4) Menampilkan tugas sekarang\n";
        std::cout << "5) Menampilkan tugas yang sedang dikerjakan\n";
        std::cout << "6) Menampilkan tugas yang sudah selesai\n";
        std::cout << "7) Mau menghapus tugas sekarang?\n";
        std::cout << "8) Mau menghapus tugas yang sedang dikerjakan?\n";
        std::cout << "9) Mau menghapus tugas yang sudah selesai?\n";
        std::cout << "10) Mau mengedit tugas\n";
        std::cout << "11) Mau mengedit tugas yang sedang dikerjakan?\n";
        std::cout << "12) Mau mengedit tugas yang sudah selesai?\n";
        std::cout << "13) Mau logout dari program?\n";
        std::cout << "14) Mau registrasi akun baru?\n";
        std::cout << "15) Keluar dari program\n";
        std::cout << "Pilih menu yang mau anda lakukan(1-15): ";
        std::cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            std::cout << "\033[2J\033[1;1H";
            data.AddTask();
            break;
        case 2:
            std::cout << "\033[2J\033[1;1H";
            data.TasktoDo();
            break;
        case 3:
            std::cout << "\033[2J\033[1;1H";
            //data.CompletedTask();
            break;
        case 4:
            std::cout << "\033[2J\033[1;1H";
            //data.DisplayTask();
            break;
        case 5:
            std::cout << "\033[2J\033[1;1H";
            //data.DisplayTaskToDo();
            break;
        case 6:
            std::cout << "\033[2J\033[1;1H";
            //data.DisplayCompletedTask();
            break;
        case 7:
            std::cout << "\033[2J\033[1;1H";
            //data.RemoveTask();
            break;
        case 8:
            std::cout << "\033[2J\033[1;1H";
            //data.RemoveTaskToDo();
            break;
        case 9:
            std::cout << "\033[2J\033[1;1H";
            //data.RemoveFinishTask();
            break;
        case 10:
            std::cout << "\033[2J\033[1;1H";
            //data.EditTask();
            break;
        case 11:
            std::cout << "\033[2J\033[1;1H";
            //data.EditTaskTodo();
            break;
        case 12:
            std::cout << "\033[2J\033[1;1H";
            //data.EditFinishTask();
            break;
        case 13:
            std::cout << "\033[2J\033[1;1H";
            credentials.LoginProgram();
            break;
        case 14:
            std::cout << "\033[2J\033[1;1H";
            credentials.ProcessRegister();
            break;
        case 15:
            std::cout << "Anda memilih keluar...";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            return 0;
        default:
            std::cout << "Pilihan anda tidak ada";
        }
        std::cout << std::endl;
        std::cout << "1) Lanjut\n"
                  << "2) Keluar\n";
        std::cout << "Ingin lanjut ke program atau keluar? ";
        std::cin >> ulang;
    } while (ulang != '2');
    return 0;
}
