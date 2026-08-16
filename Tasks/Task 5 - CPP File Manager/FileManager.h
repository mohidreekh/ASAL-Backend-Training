#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include "Utils.h"

using namespace std;

namespace fs = std::filesystem;

class FileManager
{
private:
    fs::path currentPath;

public:

    FileManager(fs::path initPath = "C:/MyFileManager")
        : currentPath(initPath)
    {
        if (!fs::exists(currentPath))
        {
            fs::create_directories(currentPath);
        }
    }

    void printFileContent(const fs::path& filePath)
    {
        ifstream file(filePath);

        if (!file.is_open())
        {
            cout << "Failed to open file.\n";
            return;
        }

        string line;

        cout << filePath.string() << " \n";
        cout << "-------------------------------------------------------------------\n";
        while (getline(file, line))
        {
            cout << line << '\n';
        }
        cout << "-------------------------------------------------------------------\n";

    }

    void createNewFile(const string& fileName)
    {
        fs::path filePath = currentPath / fileName;

        ofstream file(filePath);

        if (!file)
        {
            cout << "Failed to create file.\n";
            return;
        }

        cout << "File created successfully.\n";
    }

    void writeToFile(const string& fileName)
    {
        fs::path filePath = currentPath / fileName;

        //Before
        printFileContent(filePath);

        ofstream file(filePath);

        if (!file)
        {
            cout << "Failed to open file.\n";
            return;
        }

        string content = Utils::readLine("Enter content: ");

        file << content;
        file.close();
        //After
        printFileContent(filePath);
    }

    void appendToFile(const string& fileName)
    {
        fs::path filePath = currentPath / fileName;

        //Before
        printFileContent(filePath);

        ofstream file(filePath, ios::app);

        if (!file)
        {
            cout << "Failed to open file.\n";
            return;
        }

        string content = Utils::readLine("Enter content: ");

        file << content;

        //After
        printFileContent(filePath);
    }

    void readFile(const string& fileName)
    {
        fs::path filePath = currentPath / fileName;

        printFileContent(filePath);
    }

    void copyFile(const string& sourceName, const string& destinationName)
    {
        fs::path source = currentPath / sourceName;
        fs::path destination = currentPath / destinationName;

        if (!fs::exists(source))
        {
            cout << "Source file does not exist.\n";
            return;
        }

        try
        {
            fs::copy_file(source, destination, fs::copy_options::overwrite_existing);
            cout << "File copied successfully.\n";
        }
        catch (const fs::filesystem_error& e)
        {
            cout << "Copy failed: " << e.what() << '\n';
        }
    }

    void renameFile(const string& oldName, const string& newName)
    {
        fs::path oldPath = currentPath / oldName;
        fs::path newPath = currentPath / newName;

        if (!fs::exists(oldPath))
        {
            cout << "File does not exist.\n";
            return;
        }

        try
        {
            fs::rename(oldPath, newPath);

            cout << "File renamed successfully.\n";
        }
        catch (const fs::filesystem_error& e)
        {
            cout << "Rename failed: " << e.what() << '\n';
        }
    }

    void deleteFile(const string& fileName)
    {
        fs::path filePath = currentPath / fileName;

        if (!fs::exists(filePath))
        {
            cout << "File does not exist.\n";
            return;
        }

        try
        {
            fs::remove(filePath);
            cout << "File deleted successfully.\n";
        }
        catch (const fs::filesystem_error& e)
        {
            cout << "Delete failed: " << e.what() << '\n';
        }
    }

    void searchText(const string& fileName, const string& text)
    {
        fs::path filePath = currentPath / fileName;

        ifstream file(filePath);

        if (!file)
        {
            cout << "Failed to open file.\n";
            return;
        }

        string line;
        int lineNumber = 1;
        bool found = false;

        while (getline(file, line))
        {
            if (line.find(text) != string::npos)
            {
                cout << "Found at line " << lineNumber << ": " << line << '\n';
                found = true;
            }

            lineNumber++;
        }

        if (!found)
        {
            cout << "Text not found.\n";
        }
    }

    void displayFileInformation(const string& fileName)
    {
        fs::path filePath = currentPath / fileName;

        if (!fs::exists(filePath))
        {
            cout << "File does not exist.\n";
            return;
        }

        cout << "\n----- File Information -----\n";
        cout << "Name: " << filePath.filename().string() << '\n';
        cout << "Path: " << fs::absolute(filePath).string() << '\n';
        cout << "Extension: " << filePath.extension().string() << '\n';
        cout << "Size: " << fs::file_size(filePath) << " bytes\n";
        cout << "----------------------------\n";
    }

    void listFiles()
    {
        cout << "\n----- Files -----\n";
        for (const auto& entry : fs::directory_iterator(currentPath))
        {
            cout << entry.path().filename().string();

            if (entry.is_directory())
                cout << " [DIR]";

            cout << '\n';
        }
        cout << "-----------------\n";
    }
};