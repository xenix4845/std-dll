#include <stdio.h>
#include <windows.h>
#include <intrin.h>
#include <vadefs.h>
#include <stdbool.h>

void printCPUInfo() {
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    int cores = sysInfo.dwNumberOfProcessors;
    printf("CPU 코어 수: %d\n", cores);

    int cpuInfo[4] = { 0, 0, 0, 0 };
    __cpuid(cpuInfo, 1);
    int threads = (cpuInfo[1] >> 16) & 0xFF;
    printf("CPU 스레드 수: %d\n", threads);

    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    double ramCapacityGB = (double)memInfo.ullTotalPhys / (1024 * 1024 * 1024);
    printf("RAM 용량: %.2f GB\n", ramCapacityGB);

    #define MAX_GPUS 10
    DISPLAY_DEVICE gpuInfo;
    gpuInfo.cb = sizeof(DISPLAY_DEVICE);
    DWORD gpuIndex = 0;
    int gpuCount = 0;
    char foundGPUs[MAX_GPUS][128]; // Array to store found GPUs
    while (EnumDisplayDevices(NULL, gpuIndex, &gpuInfo, 0)) {
        if (strstr(gpuInfo.DeviceString, "AMD") || strstr(gpuInfo.DeviceString, "NVIDIA")) {
            // Check if GPU is already found

            bool found = false;
            for (int i = 0; i < gpuCount; i++) {
                if (strcmp(gpuInfo.DeviceString, foundGPUs[i]) == 0) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                printf("GPU 이름: %s\n", gpuInfo.DeviceString);
                strcpy(foundGPUs[gpuCount], gpuInfo.DeviceString); // Store found GPU
                gpuCount++;
            }
        }
        gpuIndex++;
    }
    printf("탐지된 그래픽 유닛: %d\n", gpuCount);

    // Print drive information
    DWORD drives = GetLogicalDrives();
    char driveName[] = "A:\\";
    while (drives) {
        if (drives & 1) {
            ULARGE_INTEGER freeBytesAvailable, totalBytes, totalFreeBytes;
            driveName[0] = 'A' + (driveName[0] - 'A');
            GetDiskFreeSpaceEx(driveName, &freeBytesAvailable, &totalBytes, &totalFreeBytes);
            WCHAR driveNameW[4];
            MultiByteToWideChar(CP_UTF8, 0, driveName, -1, driveNameW, 4);
            printf("드라이브 %ls - 용량: %.2f GB\n", driveNameW, (double)totalBytes.QuadPart / (1024 * 1024 * 1024));
        }
        drives >>= 1;
        ++driveName[0];
    }
}

int main() {
    printCPUInfo();
    return 0;
}
