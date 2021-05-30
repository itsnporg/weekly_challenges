#pragma once

#include <boost/asio/ip/tcp.hpp>
#include <memory>
#include <future>

#include "Url.h"

class WebRequestAbstract
{
public:
    WebRequestAbstract(boost::asio::io_context &ctx) : _resolver{ctx} {}

    virtual void Connect(Url &url) = 0;
    virtual std::future<void> async_Connect(Url &url) = 0;

    virtual std::string Get(std::string_view reqHeader) = 0;
    virtual std::future<std::string> async_Get(std::string_view reqHeader) = 0;
    
    virtual std::string Get_pipeline(std::string_view reqHeader, std::string_view end_reqHeader, size_t num) = 0;
    virtual std::future<std::string> async_Get_pipeline(std::string_view reqHeader, std::string_view end_reqHeader, size_t num) = 0;

    virtual ~WebRequestAbstract()
    {
    }

protected:
    boost::asio::ip::tcp::resolver _resolver;
};

typedef std::unique_ptr<WebRequestAbstract> WebRequest;