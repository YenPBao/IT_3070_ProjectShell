#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <ctime>
#include <windows.h>
#include <unordered_set>
#include <vector>
#include <string>

using namespace std;

class SystemUtils
{
public:
    inline static const unordered_set<string> supportedCommands = {
        "time",
        "date",
        "uptime",
        "cpuinfo",
        "meminfo",
        "diskinfo",
        "calculator"};

    const unordered_set<string> &getSupportedCommands()
    {
        return supportedCommands;
    }

    void exitShell()
    {
        cout << "Exiting Tiny Shell." << endl;
        exit(0);
    }

    void showSystemTime(const vector<string> &args)
    {
        if (!args.empty())
        {
            cerr << "Usage: time" << endl;
            return;
        }

        time_t t = time(nullptr);
        tm *now = localtime(&t);

        cout << "Current system time: "
             << (now->tm_year + 1900) << '-'
             << (now->tm_mon + 1) << '-'
             << now->tm_mday << ' '
             << now->tm_hour << ':'
             << now->tm_min << ':'
             << now->tm_sec << endl;
    }

    void showSystemDate(const vector<string> &args)
    {
        if (!args.empty())
        {
            cerr << "Usage: date" << endl;
            return;
        }

        time_t t = time(nullptr);
        tm *now = localtime(&t);

        cout << "Current system date: "
             << (now->tm_year + 1900) << '-'
             << (now->tm_mon + 1) << '-'
             << now->tm_mday << endl;
    }

    void showSystemUptime(const vector<string> &args)
    {
        if (!args.empty())
        {
            cerr << "Usage: uptime" << endl;
            return;
        }

        DWORD uptime = GetTickCount64() / 1000;
        DWORD seconds = uptime % 60;
        DWORD minutes = (uptime / 60) % 60;
        DWORD hours = (uptime / 3600) % 24;
        DWORD days = uptime / 86400;

        cout << "System uptime: "
             << days << " days, "
             << hours << " hours, "
             << minutes << " minutes, "
             << seconds << " seconds" << endl;
    }

    void showCPUInfo(const vector<string> &args)
    {
        if (!args.empty())
        {
            cerr << "Usage: cpuinfo" << endl;
            return;
        }

        SYSTEM_INFO sysInfo;
        GetSystemInfo(&sysInfo);

        cout << "CPU Information:" << endl;
        cout << "Number of processors: " << sysInfo.dwNumberOfProcessors << endl;
        cout << "Processor type: " << sysInfo.dwProcessorType << endl;
    }

    void showMemoryInfo(const vector<string> &args)
    {
        if (!args.empty())
        {
            cerr << "Usage: meminfo" << endl;
            return;
        }

        MEMORYSTATUSEX statex;
        statex.dwLength = sizeof(statex);
        GlobalMemoryStatusEx(&statex);

        cout << "Memory Information:" << endl;
        cout << "Total physical memory: " << statex.ullTotalPhys / (1024 * 1024) << " MB" << endl;
        cout << "Available physical memory: " << statex.ullAvailPhys / (1024 * 1024) << " MB" << endl;
        cout << "Total virtual memory: " << statex.ullTotalPageFile / (1024 * 1024) << " MB" << endl;
        cout << "Available virtual memory: " << statex.ullAvailPageFile / (1024 * 1024) << " MB" << endl;
    }

    void showDiskInfo(const vector<string> &args)
    {
        if (args.size() != 1)
        {
            cerr << "Usage: diskinfo <drive_letter>" << endl;
            return;
        }

        string drive = args[0] + ":\\";
        ULARGE_INTEGER avail, total, free;

        if (GetDiskFreeSpaceExA(drive.c_str(), &avail, &total, &free))
        {
            cout << "Disk Information for drive " << drive << ":" << endl;
            cout << "Total space: " << total.QuadPart / (1024 * 1024 * 1024) << " GB" << endl;
            cout << "Free space: " << free.QuadPart / (1024 * 1024 * 1024) << " GB" << endl;
        }
        else
        {
            cerr << "Failed to get disk information: " << GetLastError() << endl;
        }
    }

    void showCalculator(const vector<string> &args)
    {
        if (!args.empty())
        {
            cerr << "Usage: calculator" << endl;
            return;
        }

        STARTUPINFO si = {sizeof(si)};
        PROCESS_INFORMATION pi;

        if (!CreateProcess(TEXT("C:\\Windows\\System32\\calc.exe"), NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
        {
            cerr << "Failed to start calculator: " << GetLastError() << endl;
            return;
        }

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
};

#endif // UTILS_H
