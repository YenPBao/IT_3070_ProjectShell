#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <unordered_set>

using namespace std;

class EnvironmentManager
{
public:
    // Các lệnh hỗ trợ
    inline static const unordered_set<string> supportedCommands = {
        "add_path", "remove_path", "print_env", "set_env", "kill_env", "list_env"};

    // Hàm lấy danh sách các lệnh hỗ trợ
    const unordered_set<string> &getSupportedCommands()
    {
        return supportedCommands;
    }

    // Hàm để thêm đường dẫn vào biến môi trường PATH
    void addToPath(const string &path)
    {
        string currentPath = getEnv("PATH");
        if (currentPath.find(path) == string::npos)
        {
            string newPath = currentPath + ";" + path;
            setEnv("PATH", newPath);
            cout << "Added " << path << " to PATH." << endl;
        }
        else
        {
            cout << path << " is already in PATH." << endl;
        }
    }

    // Hàm để xóa đường dẫn khỏi biến môi trường PATH
    void removeFromPath(const string &path)
    {
        string currentPath = getEnv("PATH");
        size_t pos = currentPath.find(path);
        if (pos != string::npos)
        {
            string newPath;
            if (pos > 0 && currentPath[pos - 1] == ';')
            {
                newPath = currentPath.substr(0, pos - 1) + currentPath.substr(pos + path.length());
            }
            else if (pos + path.length() < currentPath.length() && currentPath[pos + path.length()] == ';')
            {
                newPath = currentPath.substr(0, pos) + currentPath.substr(pos + path.length() + 1);
            }
            else
            {
                newPath = currentPath.substr(0, pos) + currentPath.substr(pos + path.length());
            }
            setEnv("PATH", newPath);
            cout << "Removed " << path << " from PATH." << endl;
        }
        else
        {
            cout << path << " is not in PATH." << endl;
        }
    }

    // Hàm để in ra giá trị của biến môi trường
    void printEnv(const string &var)
    {
        string value = getEnv(var);
        if (!value.empty())
        {
            cout << var << " = " << value << endl;
        }
        else
        {
            cout << var << " is not set." << endl;
        }
    }

    // Hàm để thiết lập giá trị của biến môi trường
    void setEnv(const string &var, const string &value)
    {
        string actualValue = getEnv(value);
        _putenv_s(var.c_str(), actualValue.empty() ? value.c_str() : actualValue.c_str());
    }

    // Hàm để xóa biến môi trường
    void unsetEnv(const string &var)
    {
        _putenv_s(var.c_str(), "");
        cout << "Unset variable " << var << endl;
    }

    // Hàm để kiểm tra xem một đường dẫn có trong PATH hay không
    bool isInPath(const string &path)
    {
        return getEnv("PATH").find(path) != string::npos;
    }

    // Hàm để liệt kê tất cả các biến môi trường
    void listAllEnv()
    {
        extern char **environ;
        for (char **env = environ; *env; ++env)
        {
            cout << *env << endl;
        }
    }

    // Hàm để lấy giá trị của biến môi trường
    string getEnv(const string &var)
    {
        const char *value = getenv(var.c_str());
        return value ? string(value) : "";
    }
};

#endif // ENVIRONMENT_H
