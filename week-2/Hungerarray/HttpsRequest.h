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

    void benchmark(Url &url, std::string reqHeader) override;

    ~HttpsRequest() override;
private:
    void Setup_socket(Url &url);

    void socket_con_handshake(Url &url);

    void handle_resolve(const boost::system::error_code &ec, boost::asio::ip::tcp::resolver::results_type endpoints);

    void handle_connect(const boost::system::error_code &er, boost::asio::ip::tcp::endpoint endpoint);

    void handle_handshake(const boost::system::error_code &er);

    void handle_write(const boost::system::error_code &er, size_t snt);

    void handle_read(std::shared_ptr<std::string> buf, const boost::system::error_code &er, size_t recv);

private:
    boost::asio::ssl::context _ctx;
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> _ssl_socket;
    std::string _reqHeader;
    size_t count = 0;
};