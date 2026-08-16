#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include<climits>

using namespace std;
namespace fs = std::filesystem;


class Utils
{
public:

    static string readString(const string& message)
    {
        cout << message;

        string value;
        cin >> value;

        return value;
    }

    static string readLine(const string& message)
    {
        cout << message;

        string value;
        cin.ignore();
        getline(cin, value);

        return value;
    }

    static int readNumber(string message, int min = INT_MIN, int max = INT_MAX)
    {
        int value;

        while (true)
        {
            cout << message;

            if (!(cin >> value))
            {
                cout << "Invalid input. Please enter a number.\n";

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                continue;
            }

            if (value < min || value > max)
            {
                cout << "Please enter a number between "
                    << min << " and " << max << ".\n";
                continue;
            }

            return value;
        }
    }
};


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
            fs::copy_file(
                source,
                destination,
                fs::copy_options::overwrite_existing
            );

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
                cout << "Found at line "
                    << lineNumber
                    << ": "
                    << line
                    << '\n';

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

        cout << "Name: "
            << filePath.filename().string()
            << '\n';

        cout << "Path: "
            << fs::absolute(filePath).string()
            << '\n';

        cout << "Extension: "
            << filePath.extension().string()
            << '\n';

        cout << "Size: "
            << fs::file_size(filePath)
            << " bytes\n";

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


int main()
{
    FileManager fm;

    int choice;

    do
    {
        cout << "\n================================\n";
        cout << "       C++ FILE MANAGER\n";
        cout << "================================\n";

        cout << "Current Directory: C:/MyFileManager\n\n";

        cout << "1. Create a new file\n";
        cout << "2. Write to a file\n";
        cout << "3. Append to a file\n";
        cout << "4. Read a file\n";
        cout << "5. Copy a file\n";
        cout << "6. Rename a file\n";
        cout << "7. Delete a file\n";
        cout << "8. Search text in a file\n";
        cout << "9. Display file information\n";
        cout << "10. List files\n";
        cout << "0. Exit\n";

        cout << "================================\n";

        choice = Utils::readNumber("Enter your choice: ");

        switch (choice)
        {
        case 1:
            fm.createNewFile(
                Utils::readString("Enter file name: ")
            );
            break;

        case 2:
            fm.writeToFile(
                Utils::readString("Enter file name: ")
            );
            break;

        case 3:
            fm.appendToFile(
                Utils::readString("Enter file name: ")
            );
            break;

        case 4:
            fm.readFile(
                Utils::readString("Enter file name: ")
            );
            break;

        case 5:
        {
            string source =
                Utils::readString("Enter source file name: ");

            string destination =
                Utils::readString("Enter destination file name: ");

            fm.copyFile(source, destination);
            break;
        }

        case 6:
        {
            string oldName =
                Utils::readString("Enter current file name: ");

            string newName =
                Utils::readString("Enter new file name: ");

            fm.renameFile(oldName, newName);
            break;
        }

        case 7:
            fm.deleteFile(
                Utils::readString("Enter file name: ")
            );
            break;

        case 8:
        {
            string fileName =
                Utils::readString("Enter file name: ");

            string text =
                Utils::readString("Enter text to search: ");

            fm.searchText(fileName, text);
            break;
        }

        case 9:
            fm.displayFileInformation(
                Utils::readString("Enter file name: ")
            );
            break;

        case 10:
            fm.listFiles();
            break;

        case 0:
            cout << "Goodbye!\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}