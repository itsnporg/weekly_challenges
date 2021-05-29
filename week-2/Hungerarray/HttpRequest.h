#pragma once

#include "WebRequestAbstract.h"
#include <boost/asio/io_context.hpp>

class HttpRequest : public WebRequestAbstract
{
public:
    HttpRequest(boost::asio::io_context &io_ctx);

    void async_ConnectAndGet(Url &url, std::string_view reqHeader) override;

    void Connect(Url &url) override;
    std::future<void> async_Connect(Url &url) override;

    std::string Get(std::string_view reqHeader) override;
    std::future<std::string> async_Get(std::string_view reqHeader) override;
    
    void benchmark(Url &url, std::string reqHeader) override;



    ~HttpRequest() override;

private:
    void handle_resolve(const boost::system::error_code &er, boost::asio::ip::tcp::resolver::results_type endpoints);

    void handle_connect(const boost::system::error_code &er,
    boost::asio::ip::tcp::endpoint endpoint);

    void handle_write(const boost::system::error_code &er, size_t snt);

    void handle_read(std::shared_ptr<std::string> response, const boost::system::error_code &er, size_t recv);

private:
    boost::asio::ip::tcp::socket _socket;
    std::string _reqHeader;
    size_t count = 0;
};