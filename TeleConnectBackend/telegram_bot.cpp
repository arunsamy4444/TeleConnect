#include <cstdlib>
#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
    std::string BOT_TOKEN = "8437194783:AAEXkdvcsuuulhd0hjM3PNhlhTyDJQ1vlfc";
    std::string CHAT_ID = "1482060987";

    std::string message = "Hello World"; 
    if (argc > 1) message = argv[1]; // take message from Node

    std::string cmd = "curl -s \"https://api.telegram.org/bot" + BOT_TOKEN +
                      "/sendMessage?chat_id=" + CHAT_ID + "&text=" + message + "\"";

    int ret = system(cmd.c_str());
    if (ret == 0) std::cout << "Message sent successfully!\n";
    else std::cerr << "Failed to send message.\n";

    return 0;
}

