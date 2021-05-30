#include <iostream>
#include <memory>
#include <boost/asio/connect.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>

#include "HttpRequest.h"

using namespace boost;
using namespace boost::asio::ip;

HttpRequest::HttpRequest(asio::io_context &io_ctx)
    : WebRequestAbstract{io_ctx},
      _socket{io_ctx}
{
}

void HttpRequest::Connect(Url &url)
{
    auto _endpoints = _resolver.resolve(url._host, url._scheme);
    asio::connect(_socket, _endpoints);
    _socket.set_option(tcp::no_delay(true));
}

std::future<void> HttpRequest::async_Connect(Url &url)
{
    return std::async([this, &url]() -> void
                      { Connect(url); });
}

std::string HttpRequest::Get(std::string_view reqHeader)
{
    boost::system::error_code ec;
    asio::write(_socket, asio::buffer(reqHeader), ec);

    if (ec.failed()){
        std::cout << "Error on write header: " << ec.message() << std::endl;
        return std::string{};
    }

    std::string temp;
    asio::read(_socket, asio::dynamic_buffer(temp), ec);
    return temp;
}

std::future<std::string> HttpRequest::async_Get(std::string_view reqHeader)
{
    return std::async([this, reqHeader]() -> std::string
                      { return Get(reqHeader); });
}

std::string HttpRequest::Get_pipeline(std::string_view reqHeader, std::string_view end_reqHeader, size_t num)
{
     boost::system::error_code ec;
    for (size_t i = 0; i < num - 1; ++i)
    {
        asio::write(_socket, asio::buffer(reqHeader), ec);
        if(ec.failed())
            std::cout << "pipeline failed at: " << i+ 1 << ec.message() << std::endl; 
    }
    asio::write(_socket, asio::buffer(end_reqHeader), ec);

    std::string temp; 
    asio::read(_socket, asio::dynamic_buffer(temp), ec);
    return temp;
}

std::future<std::string> HttpRequest::async_Get_pipeline(std::string_view reqHeader, std::string_view end_reqHeader, size_t num)
{
    return std::async([this, reqHeader, end_reqHeader, num](){
        return Get_pipeline(reqHeader, end_reqHeader, num);
    });
}

HttpRequest::~HttpRequest()
{
    _socket.close();
}