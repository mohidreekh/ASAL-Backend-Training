#pragma once

#include "Directory.h"

#include <filesystem>
#include <string>

class FileManager
{
private:
    fs::path currentPath;
    fs::path rootPath;
    Directory* root;

private:
    fs::path getFilePath(const std::string& fileName) const;
    bool fileExists(const fs::path& path) const;

    std::string selectFile() const;
    fs::path selectItem() const;

    void printFileContent(const fs::path& filePath) const;

public:
    FileManager(fs::path initPath = "C:/MyFileManager");
    ~FileManager();

    void createNewFile();
    void createDirectory();

    std::string getCurrentPath() const;

    void writeToFile();
    void appendToFile();
    void readFile();

    void copyFile();
    void renameFile();
    void deleteFile();

    void searchText();
    void displayFileInformation();

    void openItem();
    void goBack();

    void displayTree();
};