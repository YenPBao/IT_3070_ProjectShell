#ifndef TOOL_H
#define TOOL_H

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

void showHelp(const std::vector<std::string> &args)
{
    if (!args.empty())
    {
        cerr << "Usage: help" << endl;
        return;
    }
    cout << left;
    cout << setw(20) << left << "Command" << ": Description" << endl;
    cout << setw(20) << left << "--------------------" << "------------------------------" << endl;

    cout<<setw(20)<<"Utils System Manager"<<'\n';
    cout << setw(20) << "help" << ": Show help menu" << endl;
    cout << setw(20) << "exit" << ": Exit the shell" << endl;
    cout << setw(20) << "dir" << ": List directory contents" << endl;
    cout << setw(20) << "cd" << ": Change directory" << endl;
    cout << setw(20) << "pwd" << ": Print working directory" << endl;
    cout << setw(20) << "calculator" << ": Open simple calculator" << endl;
    cout << setw(20) << "time" << ": Show system time" << endl;
    cout << setw(20) << "date" << ": Show system date" << endl;

    cout<<setw(20)<<"File and Folder Manager" << '\n';
    cout << setw(20) << "create_folder" << ": Create a directory" << endl;
    cout << setw(20) << "delete_folder" << ": Delete a directory" << endl;
    cout << setw(20) << "list_tree" << ": Display directory tree" << endl;
    cout << setw(20) << "list_file" << ": List files with extension" << endl;
    cout << setw(20) << "open" << ": Open a file" << endl;
    cout << setw(20) << "rename_file" << ": Rename a file" << endl;
    cout << setw(20) << "write" << ": Write to a file" << endl;
    cout << setw(20) << "read" << ": Read a file" << endl;
    cout << setw(20) << "delete_file" << ": Delete a file" << endl;
    cout << setw(20) << "copy_file" << ": Copy a file" << endl;
    cout << setw(20) << "create_file" << ": Create a new file" << endl;
    cout << setw(20) << "move_file" << ": Move a file" << endl;
    cout << setw(20) << "run" << ": Run a script file" << endl;

    cout<<setw(20)<<"Process Manager"<<'\n';
    cout << setw(20) << "run_fg" << ": Run a process in foreground" << endl;
    cout << setw(20) << "run_bg" << ": Run a process in background" << endl;
    cout << setw(20) << "list" << ": List running processes" << endl;
    cout << setw(20) << "stop" << ": Suspend a process" << endl;
    cout << setw(20) << "kill" << ": Terminate a process" << endl;
    cout << setw(20) << "countdown" << ": Start countdown animation" << endl;

    cout << setw(20)<<"Enviroment Path Manager" <<'\n';
    cout << setw(20) << "path" << ": List environment PATH" << endl;
    cout << setw(20) << "add_path" << ": Add to PATH environment" << endl;
    cout << setw(20) << "remove_path" << ": Remove from PATH environment" << endl;
    cout << setw(20) << "create_env" << ": Set a new environment variable" << endl;
    cout << setw(20) << "kill_env" << ": Unset an environment variable" << endl;
    cout << setw(20) << "print_env" << ": Print environment variable value" << endl;
}

void changeDirectory(const vector<std::string> &args)
{
    if (args.size() != 1)
    {
        cout << "Usage: cd <directory_path>" << endl;
        return;
    }
    filesystem::path dirPath = args[0];
    if (!filesystem::exists(dirPath) || !filesystem::is_directory(dirPath))
    {
        cout << "Directory does not exist: " << dirPath << endl;
        return;
    }
    filesystem::current_path(dirPath);
    cout << "Changed directory to " << dirPath << endl;
}

void listDirectoryContents(const vector<std::string> &args)
{
    filesystem::path dirPath = ".";
    if (args.size() == 1)
    {
        dirPath = args[0];
    }
    if (!filesystem::exists(dirPath) || !filesystem::is_directory(dirPath))
    {
        cout << "Directory does not exist: " << dirPath << endl;
        return;
    }
    for (const auto &entry : filesystem::directory_iterator(dirPath))
    {
        cout << entry.path().filename().string() << (entry.is_directory() ? "/" : "") << std::endl;
    }
}

void printWorkingDirectory(const vector<std::string> &args)
{
    cout << filesystem::current_path().string() << endl;
}
#endif // TOOL_H
