#pragma once

#include <unordered_map>
#include <string>
#include <vector>

namespace Sol
{
    
    typedef std::vector<std::unordered_map<std::string, std::string>> JsonObj;

    typedef std::pair<JsonObj, std::vector<std::string>> JsonObjWithTitle;
    class App
    {
    public:
        void Start(const std::string &);

    private:
        JsonObjWithTitle ParseCsv(const std::string &);

        std::string ConvertJsonString(const JsonObjWithTitle &);

        void WriteToJson(const std::string &, const JsonObjWithTitle &);
    };
}