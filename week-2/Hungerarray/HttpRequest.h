#pragma once

#include "WebRequestAbstract.h"
#include <boost/asio/io_context.hpp>

class HttpRequest : public WebRequestAbstract
{
public:
    HttpRequest(boost::asio::io_context &io_ctx);

    void async_ConnectAndGet(Url &url, std::string_view reqHeader) override;
    void Connect(boost::asio::ip::tcp::resolver::results_type &_endpoints) override;

    std::string Get(std::string_view reqHeader) override;

    ~HttpRequest() override;

private:
    boost::asio::ip::tcp::socket _socket;
};