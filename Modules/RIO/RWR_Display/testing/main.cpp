#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <chrono>

const char* outPath = "C:\\temp\\dcs_data.txt";

void simulateMicrocontroller() {
    std::ifstream inputFile(outPath); // Path to the file written by Export.lua
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

int changeDirectory(const char* path) {
    outPath = path;
    std::cout << "Directory changed to: " << outPath << std::endl;
}

int main() {
    std::cout << "Default directory is:" << outPath << std::endl;
    std::cout << "Would you like to change it? (y/n)" << std::endl;
    char choice;
    std::cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        std::cout << "Enter new directory:" << std::endl;
        char newPath[256];
        std::cin >> newPath;
        changeDirectory(newPath);
    }
    simulateMicrocontroller();
    return 0;
}