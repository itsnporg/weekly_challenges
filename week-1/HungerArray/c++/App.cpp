#include <regex>
#include <string>
#include <iostream>
#include <sstream>

#include "App.h"
#include "Csv.h"
#include "helpers.h"

using namespace Sol;

// @params file_name : the file name of csv file
void App::Start(const std::string &file_name)
{

    std::string jsonName = std::string{file_name};
    jsonName.replace(jsonName.find('.') + 1, 3, "json");

    JsonObjWithTitle data = ParseCsv(file_name);

    WriteToJson(jsonName, data);
    return;
}

JsonObjWithTitle App::ParseCsv(const std::string &file_name)
{
    Csv csv{file_name};

    std::vector<std::string> titles = GetTitle(csv);

    return std::make_pair(GetData(titles, csv), titles);
}

std::string App::ConvertJsonString(const JsonObjWithTitle &jsWT)
{
    static std::regex numVerify{R"((\+|-)?\d*-?(?:0|[1-9]\d*)(?:\.\d*)?(?:[eE][+-]?\d+)?)"};

    std::stringstream ss;
    const JsonObj &jsO = jsWT.first;
    const std::vector<std::string> &titles = jsWT.second;

    ss << "[\n";

    for (const auto &dict : jsO)
    {
        ss << "\t{\n";
        for (const auto &title : titles)
        {
            ss << "\t\t" << '"' << title << '"' <<" : ";
            if (std::regex_match(dict.at(title), numVerify))
                ss << dict.at(title) << '\n';
            else
                ss << '"' << dict.at(title) << '"';
            ss << ((*titles.rbegin() == title) ? "\n" : ",\n");
        }
        ss << "\t}";
        if (dict != *jsO.rbegin())
            ss << ",\n";
        else
            ss << '\n';
    }

    ss << ']';

    return std::move(ss.str());
}

void App::WriteToJson(const std::string &file_name, const JsonObjWithTitle &jsWT)
{
    std::ofstream jsonFile{file_name};

    jsonFile << ConvertJsonString(jsWT);
}
