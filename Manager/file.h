#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <fstream>
#include <csignal>
#include <conio.h>
#include <windows.h>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

class FileManager
{
public:
    FileManager()
    {
        signal(SIGINT, signalHandler);
    }

    static const unordered_set<string> supportedCommands;

    static const unordered_set<string> &getSupportedCommands()
    {
        return supportedCommands;
    }

    void writeFile(const vector<string> &args)
    {
        if (args.size() < 2)
        {
            cerr << "Usage: write_file <content> <filename> [~HEAD | ~FOOT | ~LINE N]" << endl;
            return;
        }

        string content = args[0];
        string filename = args[1];

        if (args.size() == 2)
        {
            ofstream file(filename, ios::app);
            if (!file)
            {
                cerr << "Failed to open file: " << filename << endl;
                return;
            }

            file << content << endl;
            file.close();
        }
        else if (args.size() == 3 || (args.size() == 4 && args[2] == "~LINE"))
        {
            string position = args[2];
            ifstream file_in(filename);
            if (!file_in)
            {
                cerr << "Failed to open file: " << filename << endl;
                return;
            }

            vector<string> lines;
            string line;
            while (getline(file_in, line))
            {
                lines.push_back(line);
            }
            file_in.close();

            if (position == "~HEAD")
            {
                lines.insert(lines.begin(), content);
            }
            else if (position == "~FOOT")
            {
                lines.push_back(content);
            }
            else if (position == "~LINE")
            {
                if (args.size() != 4)
                {
                    cerr << "Usage: write_file <content> <filename> ~LINE N" << endl;
                    return;
                }
                size_t line_number = stoi(args[3]) - 1;
                if (line_number < lines.size())
                {
                    lines.insert(lines.begin() + line_number, content);
                }
                else
                {
                    lines.push_back(content);
                }
            }

            ofstream file_out(filename);
            if (!file_out)
            {
                cerr << "Failed to open file for writing: " << filename << endl;
                return;
            }

            for (const auto &l : lines)
            {
                file_out << l << endl;
            }
            file_out.close();
        }
        else
        {
            cerr << "Invalid number of arguments." << endl;
        }

        cout << "Successfully wrote to file: " << filename << endl;
    }

    void readFile(const vector<string> &args)
    {
        if (args.size() < 1 || args.size() > 4)
        {
            cerr << "Usage: read_file <filename> [~HEAD N | ~FOOT N | ~RANGE M N | ~LINE N]" << endl;
            return;
        }

        string filename = args[0];
        ifstream file(filename);
        if (!file)
        {
            cerr << "Could not open file: " << filename << endl;
            return;
        }

        vector<string> lines;
        string line;
        while (getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();

        if (args.size() == 1)
        {
            printLinesWithPause(lines, 0, lines.size());
        }
        else
        {
            string position = args[1];
            if (position == "~HEAD" && args.size() == 3)
            {
                size_t n = stoi(args[2]);
                printLines(lines, 0, min(n, lines.size()));
            }
            else if (position == "~FOOT" && args.size() == 3)
            {
                size_t n = stoi(args[2]);
                printLines(lines, max((size_t)0, lines.size() - n), lines.size());
            }
            else if (position == "~RANGE" && args.size() == 4)
            {
                size_t m = stoi(args[2]) - 1;
                size_t n = stoi(args[3]) - 1;
                if (m <= n && n < lines.size())
                {
                    printLines(lines, m, n + 1);
                }
                else
                {
                    cerr << "Invalid line range." << endl;
                }
            }
            else if (position == "~LINE" && args.size() == 3)
            {
                size_t n = stoi(args[2]) - 1;
                if (n < lines.size())
                {
                    printLines(lines, n, n + 1);
                }
                else
                {
                    cerr << "Line number out of range." << endl;
                }
            }
            else
            {
                cerr << "Invalid argument format." << endl;
            }
        }
    }

    void showFileSize(const string &fileName)
    {
        try
        {
            auto fileSize = fs::file_size(fileName);
            ifstream file(fileName);
            size_t lineCount = 0;
            string line;
            while (getline(file, line)) lineCount++;

            cout << "Size of file " << fileName << ": " << fileSize << " bytes" << endl;
            cout << "Number of lines in file " << fileName << ": " << lineCount << endl;
        }
        catch (const fs::filesystem_error &e)
        {
            cerr << "Error: " << e.what() << endl;
        }
    }

    void openFile(const vector<string> &args)
    {
        if (args.size() != 1)
        {
            cout << "Usage: open <file_path>" << endl;
            return;
        }
        string path = args[0];
        ShellExecuteA(NULL, "open", path.c_str(), NULL, NULL, SW_SHOW);
    }

    void renameFile(const vector<string> &args)
    {
        if (args.size() != 2)
        {
            cout << "Usage: rename <old_file_path> <new_file_path>" << endl;
            return;
        }
        fs::path oldPath = args[0];
        fs::path newPath = args[1];
        if (!fs::exists(oldPath))
        {
            cout << "File does not exist: " << oldPath << endl;
            return;
        }
        fs::rename(oldPath, newPath);
        cout << "File renamed from " << oldPath << " to " << newPath << endl;
    }

    void createFile(const vector<string> &fileNames)
    {
        for (const auto &file : fileNames)
        {
            ofstream out(file);
            if (out) cout << "File created: " << file << endl;
            else cerr << "Failed to create: " << file << endl;
        }
    }

    void deleteFile(const vector<string> &fileNames)
    {
        for (const auto &file : fileNames)
        {
            if (fs::remove(file)) cout << "Deleted: " << file << endl;
            else cerr << "Failed to delete: " << file << endl;
        }
    }

    void checkFileExistence(const vector<string> &fileNames)
    {
        for (const auto &file : fileNames)
        {
            cout << (fs::exists(file) ? "Exists: " : "Does not exist: ") << file << endl;
        }
    }

    void printFileExtensions(const vector<string> &fileNames)
    {
        for (const auto &file : fileNames)
        {
            cout << "Extension of " << file << ": " << fs::path(file).extension() << endl;
        }
    }

    void copyFile(const vector<string> &args)
    {
        if (args.size() != 2)
        {
            cout << "Usage: copy_file <src> <dst>" << endl;
            return;
        }

        try
        {
            fs::copy_file(args[0], args[1]);
            cout << "Copied from " << args[0] << " to " << args[1] << endl;
        }
        catch (const fs::filesystem_error &e)
        {
            cerr << "Error: " << e.what() << endl;
        }
    }

    void moveFile(const vector<string> &args)
    {
        if (args.size() != 2)
        {
            cout << "Usage: move_file <src> <dst>" << endl;
            return;
        }

        try
        {
            fs::rename(args[0], args[1]);
            cout << "Moved from " << args[0] << " to " << args[1] << endl;
        }
        catch (const fs::filesystem_error &e)
        {
            cerr << "Error: " << e.what() << endl;
        }
    }

    void listFilesWithExtension(const vector<string> &args)
    {
        if (args.empty() || args.size() > 2)
        {
            cout << "Usage: list_file <directory> [extension]" << endl;
            return;
        }

        string directory = args[0];
        if (!fs::exists(directory) || !fs::is_directory(directory))
        {
            cerr << "Invalid directory: " << directory << endl;
            return;
        }

        try
        {
            string ext = args.size() == 2 ? args[1] : "";
            for (const auto &entry : fs::directory_iterator(directory))
            {
                if (entry.is_regular_file())
                {
                    if (ext.empty() || entry.path().extension() == ext)
                        cout << entry.path().filename() << endl;
                }
            }
        }
        catch (const exception &e)
        {
            cerr << "Error: " << e.what() << endl;
        }
    }

private:
    static bool interrupted;

    static void signalHandler(int)
    {
        interrupted = true;
    }

    void printLines(const vector<string> &lines, size_t start, size_t end)
    {
        for (size_t i = start; i < end; ++i)
            cout << lines[i] << endl;

        cout << "End of reading. Returning to shell..." << endl;
    }

    void printLinesWithPause(const vector<string> &lines, size_t start, size_t end)
    {
        for (size_t i = start; i < end; ++i)
        {
            cout << lines[i] << endl;
            if (interrupted)
            {
                cout << "\nReading interrupted. Returning to shell..." << endl;
                interrupted = false;
                return;
            }

            if ((i + 1) % 5 == 0 && i + 1 < end)
            {
                cout << "[READ MORE] (Press any key to continue, Ctrl+C to quit)..." << endl;
                char ch = _getch();
                if (ch == 3) return;
            }
        }
        cout << "End of reading. Returning to shell..." << endl;
    }
};

bool FileManager::interrupted = false;

const unordered_set<string> FileManager::supportedCommands = {
    "write_file", "read_file", "file_size", "open", "rename"
};

#endif // FILE_H
