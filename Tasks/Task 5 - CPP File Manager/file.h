#pragma once

#include "FileSystemItem.h"

class File : public FileSystemItem
{
public:
    File(const fs::path& path);

    void display(int depth = 0) const override;
};