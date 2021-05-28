#include <iostream>

#include "Url.h"
#include "Connect.h"

int main(int argv, char **argc)
{
    if (argv != 2)
    {
        std::cout << "./usuage url" << std::endl;
        return EXIT_FAILURE;
    }

    Url url{argc[1]};

    Connect connection{url};
    connection.Start(100);
    connection.Wait();

    return 0;
}