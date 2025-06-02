#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <tlhelp32.h>
#include <unordered_set>
#include <set>
#include <locale>
#include <codecvt>
#include <iomanip>
#include <ios>
#include <iomanip>

using namespace std;
class ProcessManager
{
public:
    static const unordered_set<string> supportedCommands;
    static const unordered_set<string> &getSupportedCommands()
    {
        return supportedCommands;
    }
    // tìm các tiến trình con của một tiến trình chacha
    DWORD findChildProcess(DWORD parentPID)
    {
        HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hProcessSnap == INVALID_HANDLE_VALUE)
        {
            cerr << "Failed to create process snapshot: " << GetLastError() << '\n';
            return 0;
        }

        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32);

        if (!Process32First(hProcessSnap, &pe32))
        {
            cerr << "Failed to retrieve process information: " << GetLastError() << '\n';
            CloseHandle(hProcessSnap);
            return 0;
        }

        DWORD childPID = 0;
        do
        {
            if (pe32.th32ParentProcessID == parentPID)
            {
                childPID = pe32.th32ProcessID;
                break;
            }
        } while (Process32Next(hProcessSnap, &pe32));

        CloseHandle(hProcessSnap);
        return childPID;
    }
    // Đợi các tiến trình con chạy
    void waitForChildProcesses (DWORD parentPID)
    {
        set<DWORD> childPIDs;
        HANDLE hProcessSnap;
        PROCESSENTRY32 pe32;
        
        hProcessSnap = CreateToolhelp32Snapshot (TH32CS_SNAPPROCESS,0);
        if (hProcessSnap == INVALID_HANDLE_VALUE)
        {
            cerr<<"Failed to create process snapshot: " << GetLastError() <<'\n';
            return;
        }

        pe32.dwSize = sizeof(PROCESSENTRY32);
        if (!Process32First(hProcessSnap, &pe32))
        {
            cerr<<" Failed to retrieve process information: " << GetLastError() <<'\n';
            CloseHandle(hProcessSnap);
            return;
        }

        do
        {
          if (pe32.th32ParentProcessID == parentPID)
          {
            childPIDs.insert(pe32.th32ProcessID);
          }
        } while (Process32Next(hProcessSnap, &pe32));

        CloseHandle (hProcessSnap);

        for (auto pid : childPIDs)
        {
            HANDLE hProcess = OpenProcess (PROCESS_ALL_ACCESS, FALSE, pid);
            if (hProcess)
            {
                WaitForSingleObject(hProcess, INFINITE);
                CloseHandle (hProcess);
                waitForChildProcesses (pid);
            }
        }      
    }
    // Hàm chạy process ở foreground
    void startProcessForeground (const vector<string> &args)
    {
        if (args.size() < 1)
        {
            cerr << "Usage: start_foreground <command>" << '\n';
            return;
        }

        string command = args[0];
        for (size_t i = 1; i < args.size(); ++i)
        {
            command += " " + args[i];
        }

        STARTUPINFOA si = {sizeof(si)};
        PROCESS_INFORMATION pi;
        char *cmd = new char[command.length() + 1];
        strcpy(cmd, command.c_str());

        if (!CreateProcessA(NULL, cmd,NULL, NULL, TRUE, 0, NULL, NULL, &si,&pi))
        {
            cerr<<"Failed to start process: "<< GetLastError() <<'\n';
            delete[] cmd;
            return;
        }

        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        waitForChildProcesses (pi.dwProcessId);

        delete[] cmd;
    }

    void startProcessBackground (const vector <string> & args)
    {
        if (args.size() < 1)
        {
            cerr<<"Usage: start <executable_path> [arguments...]" << '\n';
            return;
        }

        string command = args[0];
        for (size_t i = 1; i < args.size(); ++i)
        {
            command += " " + args[i];
        }

        STARTUPINFOA si = {sizeof(si)};
        PROCESS_INFORMATION pi;
        ZeroMemory (&pi, sizeof(pi));

        char *cmd = new char [command.length() +1];
        strcpy (cmd, command.c_str());
        if (!CreateProcessA(NULL, cmd, NULL, NULL, TRUE, CREATE_NEW_PROCESS_GROUP, NULL, NULL, &si, &pi))
        {
            cerr<< " Failed to start process: "<<GetLastError() << '\n';
            delete[] cmd;
            return;
        }
        cout << "Started process with PID: "<<pi.dwProcessId << '\n';

        Sleep(1000);
        DWORD childPID = findChildProcess(pi.dwProcessId);
        if (childPID != 0)
        {
            cout<<"Detectded child process with PID: " << childPID<<'\n';
        }
        else
        {
            cout<<"No child process detected for PID: " << pi.dwProcessId <<'\n';
        }

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        delete[] cmd;
    }
    // Process nhóm Background
    void startCountdownProcess()
    {
        vector<string> args = {"Processs/countdown.exe"};
        startProcessBackground(args);
    }

    // Process nhóm Foreground
    void duck()
    {

    }

    void heart()
    {
        vector<string> args = {"Processs/heart.exe"};
        startProcessBackground(args);
    }
    void suspend (const vector<string> &args)
    {
        if (args.size() != 1)
        {
            cerr<<"Usage: suspend <PID> \n";
            return;
        }
        DWORD dwProcessId = stoul(args[0]);
        HANDLE hSnapshot = CreateToolhelp32Snapshot (TH32CS_SNAPTHREAD, 0);
        if (hSnapshot == INVALID_HANDLE_VALUE)
        {
            cerr << " System error! \n";
            return;
        }

        THREADENTRY32 te;
        te.dwSize = sizeof(THREADENTRY32);

        if (!Thread32First(hSnapshot, &te))
        {
            CloseHandle(hSnapshot);
            cerr << "System error! \n";
            return;
        }

        do 
        {
            if (te.th32OwnerProcessID == dwProcessId)
            {
                HANDLE hThread = OpenThread (THREAD_SUSPEND_RESUME, FALSE, te.th32ThreadID);
                if (hThread != NULL)
                {
                    SuspendThread(hThread);
                    CloseHandle(hThread);
                }
                else
                {
                    cerr <<"System error! \n";
                    return;
                }
            }
        }while (Thread32Next(hSnapshot, &te));

            CloseHandle(hSnapshot);
    }
    
    void resume (const vector<string> &args)
    {
        if (args.size() != 1)
        {
            cerr <<"Usage: resume <PID> \n";
            return;
        }
        DWORD dwProcessId = stoul(args[0]);

        HANDLE hSnapshot = CreateToolhelp32Snapshot (TH32CS_SNAPTHREAD, 0);
        if (hSnapshot == INVALID_HANDLE_VALUE)
        {
            cerr << "System error!\n";
            return;
        }

        THREADENTRY32 te;
        te.dwSize = sizeof(THREADENTRY32);

        if (!Thread32First(hSnapshot, &te))
        {
            CloseHandle (hSnapshot);
            cerr << "System error! \n";
            return;
        }

        do
        {
            if (te.th32OwnerProcessID == dwProcessId)
            {
                HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, te.th32ThreadID);
                if (hThread != NULL)
                {
                    ResumeThread (hThread);
                    CloseHandle(hThread);
                }
                else
                {
                    cerr<< "System error! \n";
                    return;
                }
            }
        }while (Thread32Next(hSnapshot, &te));

        CloseHandle(hSnapshot);
    }

    void listProcesses (const vector<string> &args)
    {
        HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
        if (hProcessSnap == INVALID_HANDLE_VALUE)
        {
            cerr << " Failed to create process snapshot: " << GetLastError() <<'\n';
            return;
        }

        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32);
        if (!Process32First(hProcessSnap, &pe32))
        {
            cerr<< " Failed to retrieve process information: " << GetLastError() <<'\n';
            CloseHandle (hProcessSnap);
            return;
        }
        cout<< left <<setw(8) <<"PID"<< setw(50) << "Process Name" << "Status"<< '\n';
        cout<<"----------------------------------" <<'\n';
         do
         {
            #ifdef UNICODE
            wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
            string processName = converter.to_bytes(pe32.szExeFile);
            #else
            std::string processName = pe32.szExeFile;
            #endif
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pe32.th32ProcessID);
            string processStatus = "Unknown";
            if (hProcess)
            {
                DWORD exitCode;
                if(GetExitCodeProcess (hProcess, &exitCode))
                {
                    if (exitCode = STILL_ACTIVE)
                    {
                        processStatus = "Running";
                    }
                    else
                    {
                        processStatus = "Terminated";
                    }
                }
                CloseHandle(hProcess);
            }
            else
            {
                processStatus = "Access Denied";
            }
            cout<< left <<setw(8) <<pe32.th32ProcessID << setw(50) << processName << processStatus<< '\n';
         } while (Process32Next(hProcessSnap, &pe32));

         CloseHandle (hProcessSnap);
    }

    void terminateProcess (const vector <string> &args)
    {
        if (args.size() != 1)
        {
            cout<< " Usage: terminate <pid>" <<'\n';
            return;
        }

        DWORD pid = stoul (args[0]);

        HANDLE hProcess = OpenProcess (PROCESS_QUERY_INFORMATION | PROCESS_TERMINATE, FALSE, pid);
        if (!hProcess)
        {
            DWORD error = GetLastError();
            cerr << " Failed to open process for querying and termination: " << error <<'\n';
            if (error == ERROR_ACCESS_DENIED)
            {
                cerr <<" Access denied. Please run the shell as administrator" <<'\n';
            }
            else if (error == ERROR_INVALID_PARAMETER)
            {
                cerr<< " Invalid parameter. The process might not exist" <<'\n';
            }
            return;
        }

        if (!TerminateProcess(hProcess, 0))
        {
            DWORD error = GetLastError();
            cerr<< "Failed to terminate process: " << error <<'\n';
        }
        else
        {
            cout<<" Terminated process with PID: " << pid<<'\n';
        }

        CloseHandle(hProcess);
    }

};
const std::unordered_set<std::string> ProcessManager::supportedCommands = {
    "run_fg",
    "run_bg",
    "stop",
    "resume",
    "list",
    "kill",
    "list_children"};
#endif // PROCESS_H