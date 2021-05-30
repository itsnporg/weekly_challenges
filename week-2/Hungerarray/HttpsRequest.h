#pragma once

#include <boost/asio/ssl.hpp>

#include "WebRequestAbstract.h"

class HttpsRequest : public WebRequestAbstract
{
public:
    HttpsRequest(boost::asio::io_context &ctx);

    void Connect(Url &url) override;
    std::future<void> async_Connect(Url &url) override;

    std::string Get(std::string_view reqHeader) override;
    std::future<std::string> async_Get(std::string_view reqHeader) override;

    std::string Get_pipeline(std::string_view reqHeader, std::string_view end_reqHeader, size_t num) override;
    std::future<std::string> async_Get_pipeline(std::string_view reqHeader, std::string_view end_reqHeader, size_t num) override;

    ~HttpsRequest() override;
private:
    void Setup_socket(Url &url);

    void socketConnectHandshake(Url &url);

private:
    boost::asio::ssl::context _ctx;
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> _ssl_socket;
    std::string _reqHeader;
    Url _url;
    size_t count = 0;
};