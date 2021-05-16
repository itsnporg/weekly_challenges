#pragma once

#include <fstream>
#include <string>

namespace Sol
{
    class Csv
    {
    public:
    
        Csv(const std::string &);

        Csv(const Csv &) = delete;
        Csv &operator=(const Csv &) = delete;

        Csv(Csv &&);
        Csv &operator=(Csv &&);

        Csv &operator>>(std::string &);

        bool eof();

    private:
        std::ifstream file_handle;
    };
}