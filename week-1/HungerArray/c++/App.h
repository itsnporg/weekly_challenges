#include <unordered_map>
#include <string>
#include <vector>

namespace Sol
{
    
    typedef std::vector<std::unordered_map<std::string, std::string>> JsonObj;
    class App
    {
    public:
        void Start(const std::string &);

    private:
        JsonObj ParseCsv(const std::string &);

        std::string ConvertJsonString(const JsonObj &);

        void WriteToJson(const std::string &, const JsonObj &);
    };
}