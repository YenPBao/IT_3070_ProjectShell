#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <iostream>
#include <filesystem>
#include <vector>
#include <unordered_set>

using namespace std;
namespace fs = std::filesystem;

class DirectoryManager
{
public:
    inline static const unordered_set<string> supportedCommands = {
        "copy_dir", "create_dir", "delete_dir", "move_dir", "list_tree"};

    const unordered_set<string> &getSupportedCommands()
    {
        return supportedCommands;
    }

    void copyDirectory(const vector<string> &args)
    {
        if (args.size() != 2)
        {
            cout << "Usage: copy <source_path> <destination_path>" << endl;
            return;
        }

        fs::path src = args[0], dst = args[1];
        if (!fs::exists(src) || !fs::is_directory(src))
        {
            cout << "Source directory does not exist: " << src << endl;
            return;
        }
        if (fs::exists(dst))
        {
            cout << "Destination already exists: " << dst << endl;
            return;
        }

        fs::copy(src, dst, fs::copy_options::recursive);
        cout << "Directory copied from " << src << " to " << dst << endl;
    }

    void createDirectory(const vector<string> &args)
    {
        if (args.size() != 1)
        {
            cout << "Usage: create <directory_path>" << endl;
            return;
        }

        fs::path dir = args[0];
        if (fs::exists(dir))
        {
            cout << "Directory already exists: " << dir << endl;
            return;
        }

        fs::create_directories(dir);
        cout << "Directory created: " << dir << endl;
    }

    void deleteDirectory(const vector<string> &args)
    {
        if (args.size() != 1)
        {
            cout << "Usage: delete <directory_path>" << endl;
            return;
        }

        fs::path dir = args[0];
        if (!fs::exists(dir))
        {
            cout << "Directory does not exist: " << dir << endl;
            return;
        }

        fs::remove_all(dir);
        cout << "Directory deleted: " << dir << endl;
    }

    void listDirectoryTree(const vector<string> &args)
    {
        if (args.size() != 1)
        {
            cout << "Usage: list_tree <directory_path>" << endl;
            return;
        }

        fs::path dir = args[0];
        if (!fs::exists(dir))
        {
            cout << "Directory does not exist: " << dir << endl;
            return;
        }

        cout << dir.string() << endl;
        listDirectoryTreeHelper(dir, 1);
    }

    void moveDirectory(const vector<string> &args)
    {
        if (args.size() != 2)
        {
            cout << "Usage: move <source_path> <destination_path>" << endl;
            return;
        }

        fs::path src = args[0], dst = args[1];
        if (!fs::exists(src))
        {
            cout << "Source directory does not exist: " << src << endl;
            return;
        }

        fs::rename(src, dst);
        cout << "Directory moved from " << src << " to " << dst << endl;
    }

private:
    void listDirectoryTreeHelper(const fs::path &path, int level)
    {
        if (!fs::exists(path) || !fs::is_directory(path))
            return;

        for (const auto &entry : fs::directory_iterator(path))
        {
            for (int i = 0; i < level; ++i)
                cout << "  ";
            cout << entry.path().filename().string() << endl;

            if (entry.is_directory())
                listDirectoryTreeHelper(entry, level + 1);
        }
    }
};

#endif // DIRECTORY_H
