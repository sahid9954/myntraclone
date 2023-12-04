#include <iostream>
#include <windows.h>
#include <psapi.h>

double GetCPUUtilization()
{
    FILETIME idleTime, kernelTime, userTime;

    if (GetSystemTimes(&idleTime, &kernelTime, &userTime))
    {
        ULONGLONG idle = (reinterpret_cast<ULARGE_INTEGER *>(&idleTime))->QuadPart;
        ULONGLONG kernel = (reinterpret_cast<ULARGE_INTEGER *>(&kernelTime))->QuadPart;
        ULONGLONG user = (reinterpret_cast<ULARGE_INTEGER *>(&userTime))->QuadPart;

        ULONGLONG total = kernel + user;
        double utilization = 100.0 * (1.0 - static_cast<double>(idle) / total);

        return utilization;
    }

    return -1.0; // Error
}

int main()
{
    double cpuUtilization = GetCPUUtilization();

    if (cpuUtilization >= 0)
    {
        std::cout << "CPU Utilization: " << cpuUtilization << "%" << std::endl;
        return static_cast<int>(cpuUtilization);
    }
    else
    {
        std::cerr << "Error retrieving CPU utilization." << std::endl;
        return -1;
    }
}
