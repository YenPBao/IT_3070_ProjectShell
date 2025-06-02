#ifndef TOOL_H
#define TOOL_H

#include <iostream>
#include <vector>
#include <iomanip>

void showHelp(const std::vector<std::string> &args)
{
    if (!args.empty())
    {
        std::cerr << "Usage: help" << std::endl;
        return;
    }
    std::cout << std::left;
    std::cout << std::setw(20) << std::left << "Command" << ": Description" << std::endl;
    std::cout << std::setw(20) << std::left << "--------------------" << "------------------------------" << std::endl;

    cout<<setw(20)<<"Quan li tien ich he thong"<<'\n';
    std::cout << std::setw(20) << "help" << ": Show help menu" << std::endl;
    std::cout << std::setw(20) << "exit" << ": Exit the shell" << std::endl;
    std::cout << std::setw(20) << "dir" << ": List directory contents" << std::endl;
    std::cout << std::setw(20) << "cd" << ": Change directory" << std::endl;
    std::cout << std::setw(20) << "pwd" << ": Print working directory" << std::endl;
    std::cout << std::setw(20) << "calculator" << ": Open simple calculator" << std::endl;
    std::cout << std::setw(20) << "time" << ": Show system time" << std::endl;
    std::cout << std::setw(20) << "date" << ": Show system date" << std::endl;

    cout<<setw(20)<<"Quan li thu muc va file";
    std::cout << std::setw(20) << "create_folder" << ": Create a directory" << std::endl;
    std::cout << std::setw(20) << "delete_folder" << ": Delete a directory" << std::endl;
    std::cout << std::setw(20) << "list_tree" << ": Display directory tree" << std::endl;
    std::cout << std::setw(20) << "list_file" << ": List files with extension" << std::endl;
    std::cout << std::setw(20) << "open" << ": Open a file" << std::endl;
    std::cout << std::setw(20) << "rename_file" << ": Rename a file" << std::endl;
    std::cout << std::setw(20) << "write" << ": Write to a file" << std::endl;
    std::cout << std::setw(20) << "read" << ": Read a file" << std::endl;
    std::cout << std::setw(20) << "delete_file" << ": Delete a file" << std::endl;
    std::cout << std::setw(20) << "copy_file" << ": Copy a file" << std::endl;
    std::cout << std::setw(20) << "create_file" << ": Create a new file" << std::endl;
    std::cout << std::setw(20) << "move_file" << ": Move a file" << std::endl;
    std::cout << std::setw(20) << "run" << ": Run a script file" << std::endl;

    cout<<setw(20)<<"Quan li tien trinh";
    std::cout << std::setw(20) << "run_fg" << ": Run a process in foreground" << std::endl;
    std::cout << std::setw(20) << "run_bg" << ": Run a process in background" << std::endl;
    std::cout << std::setw(20) << "list" << ": List running processes" << std::endl;
    std::cout << std::setw(20) << "stop" << ": Suspend a process" << std::endl;
    std::cout << std::setw(20) << "kill" << ": Terminate a process" << std::endl;
    std::cout << std::setw(20) << "dancing" << ": Display dancing animation" << std::endl;
    std::cout << std::setw(20) << "heart" << ": Display heart animation" << std::endl;
    std::cout << std::setw(20) << "countdown" << ": Start countdown animation" << std::endl;

    cout<<setw(20)<<"Quan li bien moi truong";
    std::cout << std::setw(20) << "path" << ": List environment PATH" << std::endl;
    std::cout << std::setw(20) << "add_path" << ": Add to PATH environment" << std::endl;
    std::cout << std::setw(20) << "remove_path" << ": Remove from PATH environment" << std::endl;
    std::cout << std::setw(20) << "create_env" << ": Set a new environment variable" << std::endl;
    std::cout << std::setw(20) << "kill_env" << ": Unset an environment variable" << std::endl;
    std::cout << std::setw(20) << "print_env" << ": Print environment variable value" << std::endl;
}

void changeDirectory(const std::vector<std::string> &args)
{
    if (args.size() != 1)
    {
        std::cout << "Usage: cd <directory_path>" << std::endl;
        return;
    }
    std::filesystem::path dirPath = args[0];
    if (!std::filesystem::exists(dirPath) || !std::filesystem::is_directory(dirPath))
    {
        std::cout << "Directory does not exist: " << dirPath << std::endl;
        return;
    }
    std::filesystem::current_path(dirPath);
    std::cout << "Changed directory to " << dirPath << std::endl;
}

void listDirectoryContents(const std::vector<std::string> &args)
{
    std::filesystem::path dirPath = ".";
    if (args.size() == 1)
    {
        dirPath = args[0];
    }
    if (!std::filesystem::exists(dirPath) || !std::filesystem::is_directory(dirPath))
    {
        std::cout << "Directory does not exist: " << dirPath << std::endl;
        return;
    }
    for (const auto &entry : std::filesystem::directory_iterator(dirPath))
    {
        std::cout << entry.path().filename().string() << (entry.is_directory() ? "/" : "") << std::endl;
    }
}

void printWorkingDirectory(const std::vector<std::string> &args)
{
    std::cout << std::filesystem::current_path().string() << std::endl;
}
#endif // TOOL_H
