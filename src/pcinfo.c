#include <stdio.h>
#include <windows.h>
#include <intrin.h>

void printCPUInfo() {
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    printf("CPU Cores: %d\n", sysInfo.dwNumberOfProcessors);

    int cpuInfo[4] = { 0, 0, 0, 0 };
    __cpuid(cpuInfo, 1);
    int threads = (cpuInfo[1] >> 16) & 0xFF;
    printf("CPU Threads: %d\n", threads);

    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    printf("RAM Capacity: %llu bytes\n", memInfo.ullTotalPhys);

    DISPLAY_DEVICE gpuInfo;
    gpuInfo.cb = sizeof(DISPLAY_DEVICE);
    EnumDisplayDevices(NULL, 0, &gpuInfo, 0);
    printf("GPU Name: %s\n", gpuInfo.DeviceString);

    DWORD drives = GetLogicalDrives();
    char driveName[4] = { 'A', ':', '\\', '\0' };
    for (int i = 0; i < 26; i++) {
        if (drives & 1) {
            driveName[0] = 'A' + i;
            ULARGE_INTEGER freeBytesAvailable, totalBytes, totalFreeBytes;
            GetDiskFreeSpaceEx(driveName, &freeBytesAvailable, &totalBytes, &totalFreeBytes);
            printf("Drive %s - Capacity: %llu bytes\n", driveName, totalBytes.QuadPart);
        }
        drives >>= 1;
    }
}

int main() {
    printCPUInfo();
    return 0;
}