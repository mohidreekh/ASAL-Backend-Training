#pragma once

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class FileSystemItem
{
protected:
    fs::path path;

public:
    FileSystemItem(const fs::path& path);
    virtual ~FileSystemItem();

    virtual void display(int depth = 0) const = 0;

    const fs::path& getPath() const;
    std::string getName() const;
};