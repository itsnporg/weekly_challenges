#pragma once

#include <string>

#include <boost/asio.hpp>

#include "Url.h"
class Connect
{
public:
    static boost::asio::io_context _io_context;

public:
    Connect(const Url &url) : _resolver(_io_context)
    {
        auto res = _resolver.resolve(url._host, url._scheme);
    }
private:
    boost::asio::ip::tcp::resolver _resolver;
};