#include <iostream>
#include <string>

// Minimal C++ backend for assignment demonstration
// Represents POST /api/message -> Telegram integration

void sendMessageToTelegram(const std::string& name, const std::string& msg) {
    std::cout << "Simulating sending message to Telegram...\n";
    std::cout << "Name: " << name << "\nMessage: " << msg << std::endl;
}

int main() {
    std::string name = "Arun";
    std::string msg = "Hello Telegram!";

    // Simulate API call from frontend
    sendMessageToTelegram(name, msg);

    std::cout << "Frontend would send a POST request to /api/message.\n";
    std::cout << "C++ backend would forward it to Telegram.\n";
    return 0;
}
