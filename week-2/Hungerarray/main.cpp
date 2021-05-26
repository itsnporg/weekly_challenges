#include <iostream>
#include <regex>
#include <string>

#include "Url.h"

int main(int argv, char **argc)
{
    if (argv != 2)
    {
        std::cout << "./usuage url" << std::endl;
        return EXIT_FAILURE;
    }

    Url url{argc[1]};

    std::cout << "Scheme: " << url._scheme << '\n'
              << "Host: " << url._host << '\n'
              << "Path: " << url._path << std::endl;
    return 0;
}