#pragma once

#include "WebRequestAbstract.h"
#include <boost/asio/io_context.hpp>

class HttpRequest : public WebRequestAbstract
{
public:
    HttpRequest(boost::asio::io_context &io_ctx);

    void Connect(Url &url) override;
    std::future<void> async_Connect(Url &url) override;

    std::string Get(std::string_view reqHeader) override;
    std::future<std::string> async_Get(std::string_view reqHeader) override;
    
    ~HttpRequest() override;

private:
    boost::asio::ip::tcp::socket _socket;
    std::string _reqHeader;
    size_t count = 0;
};