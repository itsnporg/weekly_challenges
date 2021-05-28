#include <iostream>
#include <iomanip>
#include <chrono>

#include "Url.h"
#include "Connect.h"

int main(int argv, char **argc)
{
    Url url{argc[1]};
    size_t lim = std::stoull(std::string{argc[2]});

    Connect connection{url};
    connection.Start(lim);
    connection.Wait();

    return 0;
}

