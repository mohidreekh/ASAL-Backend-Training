#include "File.h"

#include <iostream>

File::File(const fs::path& path)
    : FileSystemItem(path)
{
}

void File::display(int depth) const
{
    std::cout << std::string(depth * 2, ' ') << "[FILE] " << getName() << '\n';
}