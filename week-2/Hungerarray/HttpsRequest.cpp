#include <iostream>
#include <boost/asio/connect.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>

#include "HttpsRequest.h"

using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;

ssl::context Create_context()
{
    ssl::context ctx{ssl::context::sslv23_client};
    ctx.set_default_verify_paths();
    ctx.set_verify_mode(ssl::verify_peer);

    return ctx;
}

void HttpsRequest::async_ConnectAndGet(Url &url, std::string_view reqHeader)
{

}

void HttpsRequest::Setup_socket(Url &url)
{
    SSL_set_tlsext_host_name(_ssl_socket.native_handle(), url._host.c_str());
    _ssl_socket.set_verify_callback(ssl::rfc2818_verification(url._host));
}

HttpsRequest::HttpsRequest(io_context &ctx)
    : WebRequestAbstract{ctx},
      _ctx{Create_context()},
      _ssl_socket{ctx, _ctx}

{

}

void HttpsRequest::Connect(Url &url)
{
    Setup_socket(url);
    socket_con_handshake(url);
}

void HttpsRequest::socket_con_handshake(Url &url)
{
    auto endpoints = _resolver.resolve(url._host, url._scheme);
    boost::asio::connect(_ssl_socket.lowest_layer(), endpoints);
    boost::system::error_code ec;
    _ssl_socket.handshake(ssl::stream<tcp::socket>::client, ec);
    if (ec.failed())
    {
        std::cout << "Handshake failed: " << ec.message() << std::endl;
        return;
    }
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

HttpsRequest::~HttpsRequest()
{
    _ssl_socket.shutdown();
}