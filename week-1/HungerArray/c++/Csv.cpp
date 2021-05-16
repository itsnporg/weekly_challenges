#include <string>
#include <fstream>

#include "Csv.h"

using namespace Sol;

Csv::Csv(const std::string &file_name)
    : file_handle{file_name}
{
}

Csv::Csv(Csv &&cp)
    : file_handle{std::move(cp.file_handle)}
{
}

Csv& Csv::operator=(Csv &&cp)
{
    file_handle = std::move(cp.file_handle);
    return *this;
}

Csv& Csv::operator>>(std::string &str)
{
    std::getline(file_handle >> std::ws, str);
    return *this;
}

bool Csv::eof()
{
    return file_handle.eof();
}