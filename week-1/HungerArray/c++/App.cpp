#include <string>
#include <iostream>

#include "App.h"
#include "Csv.h"

using namespace Sol;

// @params file_name : the file name of csv file
void App::Start(const std::string &file_name)
{
    std::string jsonName = "data.json";

    JsonObj data = ParseCsv(file_name);

    WriteToJson(jsonName, data);
    return;
}

JsonObj App::ParseCsv(const std::string &file_name)
{
    return JsonObj();
}

std::string App::ConvertJsonString(const JsonObj &)
{
    return std::string();
}

void App::WriteToJson(const std::string &file_name, const JsonObj &jsO)
{
}