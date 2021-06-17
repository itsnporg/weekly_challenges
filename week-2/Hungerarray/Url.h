#pragma once

#include <string>
#include <regex>

struct Url
{
    Url(const std::string &str) : _urlStr{str}
    {
        _parse_url(_urlStr);
    }

public:
    std::string _host;
    std::string _path;
    std::string _scheme;

private:
    void _parse_url(const std::string &str)
    {
        // regex url parser
        static std::regex urlParser{R"(^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?)", std::regex::extended};
        std::smatch sm;
        std::regex_match(str, sm, urlParser);

        _scheme = sm[2];
        _host = sm[4];
        _path = sm[5];
        // adjust for empty path in url
        _path = _path.empty() ? "/" : _path;
    }

private:
    std::string _urlStr;
};