#include "FileSystemItem.h"

FileSystemItem::FileSystemItem(const fs::path& path)
    : path(path)
{
}

FileSystemItem::~FileSystemItem()
{
}

const fs::path& FileSystemItem::getPath() const
{
    return path;
}

std::string FileSystemItem::getName() const
{
    return path.filename().string();
}