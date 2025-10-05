#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cctype>
#include "json.hpp" // nlohmann/json

#pragma comment(lib, "Ws2_32.lib")
#define PORT 5000

using json = nlohmann::json;

// URL encoder
std::string urlEncode(const std::string &value) {
    std::string encoded;
    char hex[4];
    for (char c : value) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
            encoded += c;
        else {
            sprintf(hex, "%%%02X", (unsigned char)c);
            encoded += hex;
        }
    }
    return encoded;
}

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }

    SOCKET server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == INVALID_SOCKET) { std::cerr << "Socket failed\n"; return 1; }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    if (bind(server, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed\n"; return 1;
    }

    if (listen(server, 3) == SOCKET_ERROR) { std::cerr << "Listen failed\n"; return 1; }

    std::cout << "Server running on port " << PORT << "...\n";

    std::string BOT_TOKEN = "8437194783:AAEXkdvcsuuulhd0hjM3PNhlhTyDJQ1vlfc";
    std::string CHAT_ID = "1482060987";

    while (true) {
        SOCKET client = accept(server, NULL, NULL);
        if (client == INVALID_SOCKET) { std::cerr << "Accept failed\n"; continue; }

        char buffer[4096] = {0};
        int bytes = recv(client, buffer, sizeof(buffer), 0);
        std::string request(buffer, bytes);

        // Handle CORS preflight OPTIONS request
        if (request.find("OPTIONS") == 0) {
            std::string preflight = 
                "HTTP/1.1 200 OK\r\n"
                "Access-Control-Allow-Origin: *\r\n"
                "Access-Control-Allow-Methods: POST, OPTIONS\r\n"
                "Access-Control-Allow-Headers: Content-Type\r\n"
                "Content-Length: 0\r\n\r\n";
            send(client, preflight.c_str(), preflight.size(), 0);
            closesocket(client);
            continue;
        }

        // crude extraction of JSON body
        size_t bodyPos = request.find("\r\n\r\n");
        std::string body = (bodyPos != std::string::npos) ? request.substr(bodyPos + 4) : "";

        std::string name = "Anonymous";
        std::string msg  = "Hello World";

        // Parse JSON safely
        try {
            json j = json::parse(body);
            name = j.value("name", "Anonymous");
            msg  = j.value("msg", "Hello World");
        } catch (...) {
            std::cerr << "Failed to parse JSON: " << body << "\n";
        }

        // Combine and encode
        std::string finalMessage = name + ": " + msg;
        std::string finalMessageEncoded = urlEncode(finalMessage);

        // Send to Telegram
        std::string cmd = "curl -s \"https://api.telegram.org/bot" + BOT_TOKEN +
                          "/sendMessage?chat_id=" + CHAT_ID + "&text=" + finalMessageEncoded + "\"";
        int ret = system(cmd.c_str());
        if (ret == 0) std::cout << "Message sent: " << finalMessage << "\n";
        else std::cerr << "Failed to send message\n";

        // send HTTP response
        std::string httpResponse = 
            "HTTP/1.1 200 OK\r\n"
            "Access-Control-Allow-Origin: *\r\n"
            "Content-Length: 19\r\n\r\n"
            "Message sent!";
        send(client, httpResponse.c_str(), httpResponse.size(), 0);

        closesocket(client);
    }

    closesocket(server);
    WSACleanup();
    return 0;
}










// #include <winsock2.h>
// #include <ws2tcpip.h>
// #include <iostream>
// #include <string>
// #include <cstdlib>
// #include <algorithm>  // for std::remove

// #pragma comment(lib, "Ws2_32.lib")
// #define PORT 5000

// int main() {
//     WSADATA wsaData;
//     if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
//         std::cerr << "WSAStartup failed\n";
//         return 1;
//     }

//     SOCKET server = socket(AF_INET, SOCK_STREAM, 0);
//     if (server == INVALID_SOCKET) { std::cerr << "Socket failed\n"; return 1; }

//     sockaddr_in addr;
//     addr.sin_family = AF_INET;
//     addr.sin_addr.s_addr = INADDR_ANY;
//     addr.sin_port = htons(PORT);

//     if (bind(server, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
//         std::cerr << "Bind failed\n"; return 1;
//     }

//     if (listen(server, 3) == SOCKET_ERROR) { std::cerr << "Listen failed\n"; return 1; }

//     std::cout << "Server running on port " << PORT << "...\n";

//     std::string BOT_TOKEN = "8437194783:AAEXkdvcsuuulhd0hjM3PNhlhTyDJQ1vlfc";
//     std::string CHAT_ID = "1482060987";

//     while (true) {
//         SOCKET client = accept(server, NULL, NULL);
//         if (client == INVALID_SOCKET) { std::cerr << "Accept failed\n"; continue; }

//         char buffer[2048] = {0};
//         int bytes = recv(client, buffer, 2048, 0);
//         std::string request(buffer, bytes);

//         // Handle CORS preflight OPTIONS request
//         if (request.find("OPTIONS") == 0) {
//             std::string preflight = 
//                 "HTTP/1.1 200 OK\r\n"
//                 "Access-Control-Allow-Origin: *\r\n"
//                 "Access-Control-Allow-Methods: POST, OPTIONS\r\n"
//                 "Access-Control-Allow-Headers: Content-Type\r\n"
//                 "Content-Length: 0\r\n\r\n";
//             send(client, preflight.c_str(), preflight.size(), 0);
//             closesocket(client);
//             continue;
//         }

//         // crude extraction of JSON body
//         size_t bodyPos = request.find("\r\n\r\n");
//         std::string body = (bodyPos != std::string::npos) ? request.substr(bodyPos + 4) : "";

//         std::string msg = "Hello World";
//         size_t msgPos = body.find("\"msg\"");
//         if (msgPos != std::string::npos) {
//             size_t start = body.find(":", msgPos) + 1;
//             size_t end = body.find("\"", start + 1);
//             msg = body.substr(start, end - start);
//             msg.erase(std::remove(msg.begin(), msg.end(), '\"'), msg.end());
//         }

//         // send to Telegram
//         std::string cmd = "curl -s \"https://api.telegram.org/bot" + BOT_TOKEN +
//                           "/sendMessage?chat_id=" + CHAT_ID + "&text=" + msg + "\"";
//         system(cmd.c_str());

//         // send HTTP response with CORS header
//         std::string httpResponse = 
//             "HTTP/1.1 200 OK\r\n"
//             "Access-Control-Allow-Origin: *\r\n"
//             "Content-Length: 19\r\n\r\n"
//             "Message sent!";
//         send(client, httpResponse.c_str(), httpResponse.size(), 0);

//         closesocket(client);
//     }

//     closesocket(server);
//     WSACleanup();
//     return 0;
// }
