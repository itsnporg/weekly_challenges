#include <sstream>

#include "helpers.h"

#include <iostream>

using namespace Sol;

std::vector<std::string> Sol::GetTitle(Csv &ref)
{
    std::string Row = GetRow(ref);
    return GetElements(Row);
}

std::string Sol::GetRow(Csv &csv)
{
    std::string Row;
    if (csv.eof())
        return std::string();

    csv >> Row;
    return std::move(Row);
}

std::vector<std::string> Sol::GetElements(const std::string &str)
{
    if (str.empty())
        return std::vector<std::string>();

    std::stringstream ss{str};

    std::string temp;
    std::vector<std::string> ret;
    while (getline(ss >> std::ws, temp, ','))
    {
        if (!temp.empty())
            ret.push_back(temp);
    }

    return std::move(ret);
}

JsonObj Sol::GetData(const std::vector<std::string> &titles, Csv &csv)
{
    JsonObj ret;

    for (std::string temp; !csv.eof();)
    {
        temp = GetRow(csv);
        auto elem = GetElements(temp);
        std::unordered_map<std::string, std::string> dict;

        for (size_t i = 0; i < titles.size(); ++i)
        {
            dict[titles[i]] = elem[i];
        }
        ret.push_back(std::move(dict));
    }

    return ret;
}

