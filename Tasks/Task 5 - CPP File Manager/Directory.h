#pragma once

#include "FileSystemItem.h"

#include <vector>

class Directory : public FileSystemItem
{
private:
    std::vector<FileSystemItem*> children;

public:
    Directory(const fs::path& path);
    ~Directory();

    void add(FileSystemItem* item);
    void loadChildren();
    void display(int depth = 0) const override;
};