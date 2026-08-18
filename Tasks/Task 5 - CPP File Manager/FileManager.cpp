#include "FileManager.h"
#include "Utils.h"

#include <iostream>
#include <fstream>
#include <vector>

FileManager::FileManager(fs::path initPath)
    : currentPath(initPath), rootPath(initPath)
{
    if (!fs::exists(currentPath)){
        fs::create_directories(currentPath);
    }

    root = new Directory(currentPath);
    root->loadChildren();
}

FileManager::~FileManager()
{
    delete root;
}

fs::path FileManager::getFilePath(const std::string& fileName) const
{
    return currentPath / fileName;
}

bool FileManager::fileExists(const fs::path& path) const
{
    return fs::exists(path) && fs::is_regular_file(path);
}

std::string FileManager::selectFile() const
{
    std::vector<fs::path> files;

    for (const auto& entry : fs::directory_iterator(currentPath))
    {
        if (entry.is_regular_file()){
            files.push_back(entry.path());
        }
    }

    if (files.empty())
    {
        std::cout << "No files found.\n";
        return "";
    }

    std::cout << "\nFiles:\n";

    for (size_t i = 0; i < files.size(); i++)
    {
        std::cout << i + 1 << ". " << files[i].filename().string() << '\n';
    }

    int choice = Utils::readNumber("Select file: ");

    if (choice < 1 || choice > static_cast<int>(files.size()))
    {
        std::cout << "Invalid choice.\n";
        return "";
    }

    return files[choice - 1].filename().string();
}

void FileManager::printFileContent(const fs::path& filePath) const
{
    std::ifstream file(filePath);

    if (!file)
    {
        std::cout << "Failed to open file.\n";
        return;
    }

    std::string line;

    while (std::getline(file, line)) {
        std::cout << line << '\n';
    }
}

void FileManager::createNewFile()
{
    std::string fileName = Utils::readString("Enter file name: ");
    fs::path filePath = getFilePath(fileName);

    if (fs::exists(filePath))
    {
        std::cout << "File already exists.\n";
        return;
    }

    std::ofstream file(filePath);

    if (!file)
    {
        std::cout << "Failed to create file.\n";
        return;
    }

    file.close();
    root->loadChildren();

    std::cout << "File created successfully.\n";
}

void FileManager::createDirectory()
{
    std::string directoryName = Utils::readLine("Enter folder name: ");

    fs::path directoryPath = currentPath / directoryName;

    if (fs::exists(directoryPath))
    {
        std::cout << "Folder already exists.\n";
        return;
    }

    try
    {
        fs::create_directory(directoryPath);

        root->loadChildren();

        std::cout << "Folder created successfully.\n";
    }
    catch (const fs::filesystem_error& e)
    {
        std::cout << "Failed to create folder: " << e.what() << '\n';
    }
}

void FileManager::writeToFile()
{
    std::string fileName = selectFile();

    if (fileName.empty()) {
        return;
    }

    fs::path filePath = getFilePath(fileName);

    if (!fileExists(filePath))
    {
        std::cout << "File does not exist.\n";
        return;
    }

    std::cout << '\n';
    std::cout << filePath.string() << '\n';
    std::cout << "----------------------------------------\n";
    printFileContent(filePath);
    std::cout << "----------------------------------------\n";

    std::string content = Utils::readLine("Enter new content: ");

    std::ofstream file(filePath);

    if (!file)
    {
        std::cout << "Failed to open file.\n";
        return;
    }

    file << content;
    file.close();

    std::cout << '\n';
    std::cout << filePath.string() << '\n';
    std::cout << "----------------------------------------\n";
    printFileContent(filePath);
    std::cout << "----------------------------------------\n";
}

void FileManager::appendToFile()
{
    std::string fileName = selectFile();

    if (fileName.empty()){
        return;
    }

    fs::path filePath = getFilePath(fileName);

    if (!fileExists(filePath))
    {
        std::cout << "File does not exist.\n";
        return;
    }

    std::cout << '\n';
    std::cout << filePath.string() << '\n';
    std::cout << "----------------------------------------\n";
    printFileContent(filePath);
    std::cout << "----------------------------------------\n";

    std::string content = Utils::readLine("Enter content to append: ");

    std::ofstream file(filePath, std::ios::app);

    if (!file)
    {
        std::cout << "Failed to open file.\n";
        return;
    }

    file << content;
    file.close();

    std::cout << '\n';
    std::cout << filePath.string() << '\n';
    std::cout << "----------------------------------------\n";
    printFileContent(filePath);
    std::cout << "----------------------------------------\n";
}

void FileManager::readFile()
{
    std::string fileName = selectFile();

    if (fileName.empty()){
        return;
    }

    fs::path filePath = getFilePath(fileName);

    std::cout << '\n';
    std::cout << filePath.string() << '\n';
    std::cout << "----------------------------------------\n";
    printFileContent(filePath);
    std::cout << "----------------------------------------\n";
}

void FileManager::copyFile()
{
    std::string fileName = selectFile();

    if (fileName.empty()){
        return;
    }

    fs::path source = getFilePath(fileName);

    std::string destinationName = Utils::readString("Enter copy name: ");

    fs::path destination = getFilePath(destinationName);

    try
    {
        fs::copy_file(
            source,
            destination,
            fs::copy_options::overwrite_existing
        );

        root->loadChildren();

        std::cout << "File copied successfully.\n";
    }
    catch (const fs::filesystem_error& e)
    {
        std::cout << "Copy failed: " << e.what() << '\n';
    }
}

void FileManager::renameFile()
{
    std::string fileName = selectFile();

    if (fileName.empty()){
        return;
    }

    fs::path oldPath = getFilePath(fileName);

    std::string newName = Utils::readString("Enter new name: ");

    fs::path newPath = getFilePath(newName);

    try
    {
        fs::rename(oldPath, newPath);

        root->loadChildren();

        std::cout << "File renamed successfully.\n";
    }
    catch (const fs::filesystem_error& e)
    {
        std::cout << "Rename failed: " << e.what() << '\n';
    }
}

void FileManager::deleteFile()
{
    std::string fileName = selectFile();

    if (fileName.empty()){
        return;
    }

    fs::path filePath = getFilePath(fileName);

    int confirmation = Utils::readNumber("Delete this file? 1 = Yes, 0 = No: ");

    if (confirmation != 1) {
        return;
    }

    try
    {
        fs::remove(filePath);

        root->loadChildren();

        std::cout << "File deleted successfully.\n";
    }
    catch (const fs::filesystem_error& e)
    {
        std::cout << "Delete failed: " << e.what() << '\n';
    }
}

void FileManager::searchText()
{
    std::string fileName = selectFile();

    if (fileName.empty()){
        return;
    }

    std::string text = Utils::readString("Enter text to search: ");

    fs::path filePath = getFilePath(fileName);
    std::ifstream file(filePath);

    if (!file)
    {
        std::cout << "Failed to open file.\n";
        return;
    }

    std::string line;
    int lineNumber = 1;
    bool found = false;

    while (std::getline(file, line))
    {
        if (line.find(text) != std::string::npos)
        {
            std::cout << "Found at line " << lineNumber << ": " << line << '\n';

            found = true;
        }

        lineNumber++;
    }

    if (!found) {
        std::cout << "Text not found.\n";
    }
}

fs::path FileManager::selectItem() const
{
    std::vector<fs::path> items;

    for (const auto& entry : fs::directory_iterator(currentPath)){
        items.push_back(entry.path());
    }

    if (items.empty())
    {
        std::cout << "Directory is empty.\n";
        return {};
    }

    std::cout << "\nItems:\n";

    for (size_t i = 0; i < items.size(); i++)
    {
        std::cout << i + 1 << ". " << items[i].filename().string();

        if (fs::is_directory(items[i])){
            std::cout << "/";
        }

        std::cout << '\n';
    }

    int choice = Utils::readNumber("Select item: ");

    if (choice < 1 || choice > static_cast<int>(items.size()))
    {
        std::cout << "Invalid choice.\n";
        return {};
    }

    return items[choice - 1];
}

void FileManager::openItem()
{
    fs::path selectedItem = selectItem();

    if (selectedItem.empty()){
        return;
    }

    if (fs::is_directory(selectedItem))
    {
        currentPath = selectedItem;

        root->loadChildren();

        std::cout << "\nEntered: " << currentPath.string() << '\n';
    }
    else if (fs::is_regular_file(selectedItem))
    {
        std::cout << '\n';
        std::cout << selectedItem.string() << '\n';
        std::cout << "----------------------------------------\n";

        printFileContent(selectedItem);

        std::cout << "----------------------------------------\n";
    }
}

void FileManager::goBack()
{
    if (currentPath == rootPath)
    {
        std::cout << "Already at root directory.\n";
        return;
    }

    currentPath = currentPath.parent_path();

    root->loadChildren();

    std::cout << "Current path: " << currentPath.string() << '\n';
}

std::string FileManager::getCurrentPath() const
{
    return currentPath.string();
}

void FileManager::displayFileInformation()
{
    std::string fileName = selectFile();

    if (fileName.empty()){
        return;
    }

    fs::path filePath = getFilePath(fileName);

    std::cout << '\n';
    std::cout << "Name: " << filePath.filename().string() << std::endl;

    std::cout << "Path: " << fs::absolute(filePath).string() << '\n';

    std::cout << "Extension: " << filePath.extension().string() << std::endl;

    std::cout << "Size: " << fs::file_size(filePath) << " bytes" << std::endl;
}

void FileManager::displayTree()
{
    root->loadChildren();

    std::cout << "\n========== FILE TREE ==========\n";
    root->display();
    std::cout << "===============================\n";
}
