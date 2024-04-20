#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>

// Function to retrieve CPU information
void printCPUInfo() {
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    std::cout << "CPU Information:" << std::endl;
    std::cout << "Number of Cores: " << sysInfo.dwNumberOfProcessors << std::endl;
    std::cout << "Number of Threads: " << sysInfo.dwNumberOfProcessors * 2 << std::endl;
}

// Function to retrieve RAM capacity
void printRAMInfo() {
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(memInfo);
    GlobalMemoryStatusEx(&memInfo);
    std::cout << "RAM Information:" << std::endl;
    std::cout << "Total Physical Memory: " << memInfo.ullTotalPhys / (1024 * 1024) << " MB" << std::endl;
}

// Function to retrieve GPU information
void printGPUInfo() {
    // Add your code here to retrieve GPU information
    std::cout << "GPU Information:" << std::endl;
    std::cout << "GPU Model: " << "Your GPU Model" << std::endl;
}

// Function to retrieve connected hard drive information
void printHardDriveInfo() {
    // Add your code here to retrieve hard drive information
    std::cout << "Hard Drive Information:" << std::endl;
    std::cout << "Drive 1: " << "Your Drive 1 Info" << std::endl;
    std::cout << "Drive 2: " << "Your Drive 2 Info" << std::endl;
}

int main() {
    printCPUInfo();
    printRAMInfo();
    printGPUInfo();
    printHardDriveInfo();

    return 0;
}