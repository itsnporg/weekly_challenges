#include <string>
#include <iostream>

#include "App.h"
#include "Csv.h"

using namespace Sol;

// @params file_name : the file name of csv file 
void App::Start(const std::string &file_name)
{
    Csv csv(file_name);

    while(!csv.eof())
    {
        std::string temp;
        csv >> temp;
        std::cout << temp << '\n';
    }
    return;
}