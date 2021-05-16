#include <iostream>

#include "App.h"

int main(int argc, char**argv)
{
    if (argc <= 1)
    {
        std::cout << "./Usuage data.csv" << std::endl;
        return 1;
    }

    Sol::App app;
    app.Start(argv[1]);

    return 0;
}