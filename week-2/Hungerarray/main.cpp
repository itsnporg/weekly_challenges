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

     
    return 0;
}