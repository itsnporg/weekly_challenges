#pragma once

#include <boost/asio/ip/tcp.hpp>
#include <string_view>
#include <memory>
#include <sstream>

#include "Url.h"

class WebRequestAbstract
{
public:
    WebRequestAbstract(boost::asio::io_context &ctx) : _resolver{ctx} {}

    virtual void async_ConnectAndGet(Url &url, std::string_view reqHeader) = 0;

    virtual void Connect(Url &url) = 0;

    virtual std::string Get(std::string_view reqHeader) = 0;

    virtual void benchmark(Url &url, std::string reqHeader) = 0;

    void set_reqCount(size_t lim)
    {
        reqCount = lim;
    }

    size_t Get_contentLength(std::stringstream header)
    {
        size_t len;
        while (true)
        {
            if (header.str().empty())
                return 0;
            std::string temp;
            std::getline(header >> std::ws, temp);

            std::stringstream ss{temp};
            std::string type;
            ss >> type;
            if (type == "content-length:")
            {
                ss >> len;
                return len;
            }
        }
    }

    virtual ~WebRequestAbstract()
    {
    }

protected:
    boost::asio::ip::tcp::resolver _resolver;
    size_t reqCount;
};

typedef std::unique_ptr<WebRequestAbstract> WebRequest;