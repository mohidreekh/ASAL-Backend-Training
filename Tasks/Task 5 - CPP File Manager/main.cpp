#include "FileManager.h"
#include "Utils.h"

#include <iostream>

int main()
{
    FileManager fileManager;
    int choice;

    do
    {
        std::cout << "\n================================\n";
        std::cout << "        C++ FILE MANAGER\n";
        std::cout << "================================\n";
        std::cout << "Current Path: " << fileManager.getCurrentPath() << '\n';
        std::cout << "--------------------------------\n";
        std::cout << "1. Create a new file\n";
        std::cout << "2. Create a new folder\n";
        std::cout << "3. Open file/folder\n";
        std::cout << "4. Go back\n";
        std::cout << "5. Write to a file\n";
        std::cout << "6. Append to a file\n";
        std::cout << "7. Read a file\n";
        std::cout << "8. Copy a file\n";
        std::cout << "9. Rename a file\n";
        std::cout << "10. Delete a file\n";
        std::cout << "11. Search text in a file\n";
        std::cout << "12. Display file information\n";
        std::cout << "13. Display file tree\n";
        std::cout << "0. Exit\n";
        std::cout << "================================\n";

        choice = Utils::readNumber("Enter your choice: ");

        switch (choice)
        {
        case 1:
            fileManager.createNewFile();
            break;

        case 2:
            fileManager.createDirectory();
            break;

        case 3:
            fileManager.openItem();
            break;

        case 4:
            fileManager.goBack();
            break;

        case 5:
            fileManager.writeToFile();
            break;

        case 6:
            fileManager.appendToFile();
            break;

        case 7:
            fileManager.readFile();
            break;

        case 8:
            fileManager.copyFile();
            break;

        case 9:
            fileManager.renameFile();
            break;

        case 10:
            fileManager.deleteFile();
            break;

        case 11:
            fileManager.searchText();
            break;

        case 12:
            fileManager.displayFileInformation();
            break;

        case 13:
            fileManager.displayTree();
            break;

        case 0:
            std::cout << "Goodbye!\n";
            break;

        default:
            std::cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}