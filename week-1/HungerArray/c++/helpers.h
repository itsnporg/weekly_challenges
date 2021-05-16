#pragma once

#include <vector>
#include <string>

#include "App.h"
#include "Csv.h"

namespace Sol
{
    std::vector<std::string> GetTitle(Csv &ref);

    JsonObj GetData(const std::vector<std::string> &, Csv &);

    std::vector<std::string> GetElements(const std::string &);

    std::string GetRow(Csv &);
}