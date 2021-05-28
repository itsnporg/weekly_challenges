#pragma once

#include <boost/asio/ip/tcp.hpp>
#include <string_view>
#include <memory>

#include "Url.h"

class WebRequestAbstract
{
public:

    WebRequestAbstract(boost::asio::io_context &ctx) : _resolver{ctx} {}

    virtual void async_ConnectAndGet(Url &url, std::string_view reqHeader) = 0;

    virtual void Connect(boost::asio::ip::tcp::resolver::results_type &_endpoints) = 0;
    virtual std::string Get(std::string_view reqHeader) = 0;

    virtual ~WebRequestAbstract()
    {

    }
protected:
    boost::asio::ip::tcp::resolver _resolver;
};

typedef std::unique_ptr<WebRequestAbstract> WebRequest;