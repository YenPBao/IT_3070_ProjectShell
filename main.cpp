#include <bits/stdc++.h>
#include <windows.h>
#include <thread>
#include <sstream>
#include <csignal>

#include "Manager/manager.h"
using namespace std;

ProcessManager processManager;
SystemUtils systemUtils;
FileManager fileManager;
DirectoryManager directoryManager;
EnvironmentManager environmentManager;

// In ra thông tin ban đầu
void printInitialInfo()
{
    DWORD pid = GetCurrentProcessId();

    cout<<"========================================"<<'\n';
    cout<<"   ^-^  Wellcome To My Tiny Shell ^-^   "<<'\n';
    cout<<"========================================"<<'\n';
    cout<<"PID of Tiny Shell: " << pid <<'\n';
    cout<<"Please type 'help' to see the list of availble commands."<<'\n';
    cout<<"========================================"<<'\n';
}
// Hàm đọc input ra lệnh

vector<string> splitInput(const string &input)
{
    vector<string> tokens;
    string token;
    bool inQuotes = false;

    for (char ch : input)
    {
        if (ch == '\"')
        {
            inQuotes = !inQuotes;
            if (!inQuotes)
            {
                tokens.push_back(token);
                token.clear();
            }
        }
        else if (isspace(ch) && !inQuotes)
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
        }
        else if ((ch == '(' || ch == ')' || ch == ',' || ch == '+' || ch == '-' ||
                  ch == '*' || ch == '/' || ch == '<' || ch == '>') && !inQuotes)
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(string(1, ch));
        }
        else
        {
            token += ch;
        }
    }

    if (!token.empty())
    {
        tokens.push_back(token);
    }

   
    // if (!tokens.empty())
    // {
    //     tokens[0] = aliasManager.resolveAlias(tokens[0]);
    // }

    return tokens;
}
void dancing()
{
    const char *dance[] = {
        " ~~(^-^~~)",
        " ~~(^-^)~~",
        " (~~^-^)~~" };

    const int numDanceMoves = sizeof(dance) / sizeof(dance[0]);
    const int numLines = 30;
    const int delayMilliseconds = 500;

    for (int i = 0; i < numLines; ++i)
    {
        std::cout << dance[i % numDanceMoves] << '\r';
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMilliseconds));
    }
}
// Hàm thực thi lệnh 
void executeCommand (const string &command, const vector <string> &args)
{
    // Quản lí tiện ích hệ thống
    if (command == "help")
    {
        showHelp(args);
    }
    else if (command == "exit")
    {
        systemUtils.exitShell();
    }
    else if (command == "dir")
    {
        listDirectoryContents(args);
    }
    else if (command == "cd")
    {
        changeDirectory(args);
    }
    else if (command == "pwd")
    {
        printWorkingDirectory(args);
    }
    else if (command == "calculator")
    {
        systemUtils.showCalculator(args);
    }
    else if (command == "time")
    {
        systemUtils.showSystemTime(args);
    }
    else if (command == "date")
    {
        systemUtils.showSystemDate(args);
    }
    // Quản lí thư mục và file
    else if (command == "create_folder")
    {
        directoryManager.createDirectory(args);
    }
    else if (command == "delete_folder")
    {
        directoryManager.deleteDirectory(args);
    }
    else if (command == "list_tree")
    {
        directoryManager.listDirectoryTree(args);
    }
    else if (command == "list_file")
    {
        fileManager.listFilesWithExtension(args);
    }
    else if (command == "open")
    {
        fileManager.openFile(args);
    }
    else if (command == "rename_file")
    {
        fileManager.renameFile(args);
    }
    else if (command == "write")
    {
        fileManager.writeFile(args);
    }
    else if (command == "read")
    {
        fileManager.readFile(args);
    }
    else if (command == "delete_file")
    {
        fileManager.deleteFile(args);
    }
    else if (command == "copy_file")
    {
        fileManager.copyFile(args);
    }
    else if (command == "create_file")
    {
        fileManager.createFile(args);
    }
    else if (command == "move_file")
    {
        fileManager.moveFile(args);
    }
    else if (command == "run")
    {
        runScript(args);
    }
    // Quản lí tiến trình
    else if (command == "run_fg")
    {
        processManager.startProcessForeground(args);
    }
    else if (command == "run_bg")
    {
        processManager.startProcessBackground(args);
    }
    else if (command == "list")
    {
        processManager.listProcesses(args);
    }
    else if (command == "stop")
    {
        processManager.suspend(args);
    }
    else if (command == "kill")
    {
        processManager.terminateProcess(args);
    }
    else if (command == "dancing")
    {
        dancing();
    }
    else if (command == "heart")
    {
        processManager.heart();
    }
    else if (command == "countdown")
    {
        processManager.startCountdownProcess();
    }

    // Quản lí biến môi trường 
    else if (command == "path")
    {
        environmentManager.listAllEnv();
    }
    else if (command == "add_path")
    {
        if (!args.empty())
        {
            environmentManager.addToPath(args[0]);
        }
        else
        {
            std::cout << "Usage: add_path <path>" << std::endl;
        }
    }

    else if (command == "remove_path")
    {
        if (!args.empty())
        {
            environmentManager.removeFromPath(args[0]);
        }
        else
        {
            std::cout << "Usage: remove_path <path>" << std::endl;
        }
    }
    else if (command == "create_env")
    {
        if (args.size() == 3 && args[1] == "=")
        {
            environmentManager.setEnv(args[0], args[2]);
        }
        // Nếu không có tham số nào thì thông báo lỗi
        else
        {
            std::cout << "Usage: set_env <variable> = <value> or set_env <variable> = <expression>" << std::endl;
        }
    }
    else if (command == "kill_env")
    {
        if (!args.empty())
        {
            environmentManager.unsetEnv(args[0]);
        }
        else
        {
            std::cout << "Usage: unset_env <variable>" << std::endl;
        }
    }
    else if (command == "print_env")
    {
        if (!args.empty())
        {
            environmentManager.printEnv(args[0]);
        }
        else
        {
            std::cout << "Usage: print_env <variable>" << std::endl;
        }
    }
    else
    {
        cout<<"Unknown command: " << command<<'\n';
    }
}

int main ()
{
     //  In ra thông tin ban đầu khi shell khởi động
    printInitialInfo();

     // Tải lịch sử từ file (nếu có)

    std::string input;

    signal(SIGINT, SIG_IGN);

    while (true)
    {
        cout << "tiny_shell" <<">"<< std::filesystem::current_path().string() << " >" ;

        std::getline(std::cin, input);

        if (std::cin.fail() || std::cin.eof())
        {
            std::cin.clear();
            std::cout << std::endl;
            continue;
        }

        // Ghi câu lệnh vào lịch sử
       // commandHistory.add(input);

        // splitInput để tách input thành các tokens
        std::vector<std::string> tokens = splitInput(input);

        if (tokens.empty())
            continue;

        std::string command = tokens[0];

        // Xóa lệnh ra khỏi tokens => tokens chỉ còn các tham số của lệnh
        tokens.erase(tokens.begin());

        // Xử lý các lệnh còn lại
        executeCommand(command, tokens);
    }
    return 0;

}