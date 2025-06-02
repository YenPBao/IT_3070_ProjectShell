#ifndef SCRIPT_H
#define SCRIPT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <cstdlib> // For getenv

using namespace std;
namespace fs = std::filesystem;

void executeCommand(const string &command, const vector<string> &args);

vector<string> splitInput(const string &input);

string resolvePath(const string &path)
{
    // Check if the path is absolute
    if (fs::path(path).is_absolute())
    {
        return path;
    }

    // Check if the file exists in the current directory
    if (fs::exists(path))
    {
        return fs::absolute(path).string();
    }

    // Check in PATH environment variable
    const char *pathEnv = getenv("PATH");
    if (pathEnv)
    {
        vector<string> paths;
        string pathEnvStr(pathEnv);
        string delimiter = ";"; // Use ';' as the delimiter for Windows PATH

        size_t pos = 0;
        string token;
        while ((pos = pathEnvStr.find(delimiter)) != string::npos)
        {
            token = pathEnvStr.substr(0, pos);
            paths.push_back(token);
            pathEnvStr.erase(0, pos + delimiter.length());
        }
        paths.push_back(pathEnvStr);

        for (const auto &p : paths)
        {
            fs::path filePath = fs::path(p) / path;
            if (fs::exists(filePath))
            {
                return fs::absolute(filePath).string();
            }
        }
    }

    // Return the original path if no resolution found
    return path;
}

void runScript(const vector<string> &args)
{
    if (args.size() != 1)
    {
        cout << "Usage: run <script_file_path>" << endl;
        return;
    }

    string scriptPath = resolvePath(args[0]);
    ifstream scriptFile(scriptPath);
    if (!scriptFile)
    {
        cout << "Unable to open script file: " << scriptPath << endl;
        return;
    }

    string line;
    while (getline(scriptFile, line))
    {
        vector<string> tokens = splitInput(line);
        if (!tokens.empty())
        {
            string command = tokens[0];
            tokens.erase(tokens.begin());
            executeCommand(command, tokens);
        }
    }
    scriptFile.close();
}

#endif // SCRIPT_H
