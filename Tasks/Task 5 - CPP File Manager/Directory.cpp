#include "Directory.h"
#include "File.h"

#include <iostream>

Directory::Directory(const fs::path& path)
    : FileSystemItem(path)
{
}

Directory::~Directory()
{
    for (FileSystemItem* child : children)
        delete child;
}

void Directory::add(FileSystemItem* item)
{
    children.push_back(item);
}

void Directory::loadChildren()
{
    for (FileSystemItem* child : children) {
        delete child;
    }

    children.clear();

    if (!fs::exists(path) || !fs::is_directory(path))
        return;

    for (const auto& entry : fs::directory_iterator(path))
    {
        if (entry.is_directory())
        {
            Directory* directory = new Directory(entry.path());
            directory->loadChildren();
            add(directory);
        }
        else if (entry.is_regular_file())
        {
            add(new File(entry.path()));
        }
    }
}

void Directory::display(int depth) const
{
    std::cout << std::string(depth * 2, ' ') << "[DIR] " << getName() << '\n';

    for (FileSystemItem* child : children)
        child->display(depth + 1);
}