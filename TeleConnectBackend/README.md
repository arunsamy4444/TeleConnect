TeleConnectBackend

Minimal C++ Backend for Assignment Demonstration

This is a placeholder backend to show the idea of handling frontend messages and forwarding them to Telegram.

Note: Due to time constraints, this backend is not fully implemented. It simulates message handling via console output. A real backend using cpp-httplib and libcurl could be added later.

Features

Simulates receiving name and msg from the frontend

Prints messages to console to demonstrate Telegram integration

No database or security included

Usage

Open main.cpp in any C++ editor (e.g., VS Code)

Compile and run (optional):

g++ main.cpp -o TeleConnectBackend -std=c++17
./TeleConnectBackend


Observe console output simulating Telegram messages

Tech Stack

Language: C++

Frontend: React (TeleConnect app)