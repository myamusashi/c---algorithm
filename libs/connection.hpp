#include <iostream>
#include <cstdlib>
#include <cstring>
#include <chrono>
#include <thread>

// Using a namespace to prevent potential naming conflicts and to logically group
// associated functionalities.
namespace NetworkUtils {

    /**
    * @class InternetChecker
    * Checks the internet connection by pinging a reliable server.
    */
    class InternetChecker {
    private:
        /**
        * Pings a reliable server to check the internet connection.
        *
        * @param server The server to ping.
        * @return bool True if the server responds, false otherwise.
        */
        bool PingServer(const char* server) {
            std::string pingCommand = "ping -c 1 ";
            pingCommand += server;

            // Execute the ping command and capture the output.
            FILE* pipe = popen(pingCommand.c_str(), "r");
            if (!pipe) {
                return false;
            }

            char buffer[128];
            std::string result = "";
            while (!feof(pipe)) {
                if (fgets(buffer, 128, pipe) != NULL) {
                    result += buffer;
                }
            }

            pclose(pipe);

            // Check if the server responded.
            return result.find("1 packets transmitted, 1 received") != std::string::npos;
        }

    public:
        /**
        * Checks the internet connection by pinging a reliable server.
        *
        * @return bool True if the internet connection is available, false otherwise.
        */
        bool CheckInternetConnection() {
            const char* reliableServer = "8.8.8.8"; // Google Public DNS server

            // Ping the reliable server.
            bool isConnected = PingServer(reliableServer);

            return isConnected;
        }
    };
}
