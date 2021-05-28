#pragma once

#include <boost/asio/ssl.hpp>

#include "WebRequestAbstract.h"

class HttpsRequest : public WebRequestAbstract
{
public:
    HttpsRequest(boost::asio::io_context &ctx);

    void async_ConnectAndGet(Url &url, std::string_view reqHeader) override;

    void Connect(Url &url) override;


    std::string Get(std::string_view reqHeader) override;

    ~HttpsRequest() override;
private:
    void Setup_socket(Url &url);


    void socket_con_handshake(Url &url);

private:
    boost::asio::ssl::context _ctx;
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> _ssl_socket;
};