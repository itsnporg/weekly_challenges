#include <iostream>
#include <boost/asio/connect.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>

#include "HttpsRequest.h"

using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;

ssl::context Create_context()
{
    ssl::context ctx{ssl::context::sslv23_client};
    ctx.set_default_verify_paths();
    ctx.set_verify_mode(ssl::verify_none);

    return ctx;
}

HttpsRequest::HttpsRequest(io_context &ctx)
    : WebRequestAbstract{ctx},
      _ctx{Create_context()},
      _ssl_socket{ctx, _ctx},
      _url{"garbage"}
{
}

void HttpsRequest::Setup_socket(Url &url)
{
    SSL_set_tlsext_host_name(_ssl_socket.native_handle(), url._host.c_str());
    _ssl_socket.set_verify_callback(ssl::rfc2818_verification(url._host));
}


void HttpsRequest::socketConnectHandshake(Url &url)
{
    auto endpoints = _resolver.resolve(url._host, "443");
    boost::asio::connect(_ssl_socket.lowest_layer(), endpoints);
    _ssl_socket.lowest_layer().set_option(tcp::no_delay(true));
    boost::system::error_code ec;
    _ssl_socket.handshake(ssl::stream<tcp::socket>::client, ec);
    if (ec.failed())
    {
        std::cout << "Handshake failed: " << ec.message() << std::endl;
        return;
    }
}

void HttpsRequest::Connect(Url &url)
{
    Setup_socket(url);
    socketConnectHandshake(url);
}

std::future<void> HttpsRequest::async_Connect(Url &url)
{
    return std::async( [this, &url]() -> void
                      { Connect(url); });
}

std::string HttpsRequest::Get(std::string_view reqHeader)
{
    boost::system::error_code ec;
    asio::write(_ssl_socket, asio::buffer(reqHeader), ec);

    if (ec.failed())
    {
        std::cout << "Error on write header: " << ec.message() << std::endl;
        return std::string{};
    }

    std::string temp;
    asio::read(_ssl_socket, asio::dynamic_buffer(temp), ec);
    return temp;
}

std::future<std::string> HttpsRequest::async_Get(std::string_view reqHeader)
{
    return std::async([this, reqHeader]() -> std::string
                      { return Get(reqHeader); });
}

HttpsRequest::~HttpsRequest()
{
    _ssl_socket.shutdown();
}