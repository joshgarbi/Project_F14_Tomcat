#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <chrono>

void simulateMicrocontroller() {
    std::ifstream inputFile("C:\\temp\\dcs_data.txt"); // Path to the file written by Export.lua
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return;
    }

    std::string line;
    while (true) {
        // Check if there's new data in the file
        while (std::getline(inputFile, line)) {
            // Simulate processing the data
            std::cout << "Received data: " << line << std::endl;

        }

        // Clear EOF flag and wait for new data
        inputFile.clear();
    }
}

int main() {
    simulateMicrocontroller();
    return 0;
}