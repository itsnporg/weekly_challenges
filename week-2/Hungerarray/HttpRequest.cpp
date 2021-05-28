#include <iostream>
#include <memory>
#include <boost/asio/connect.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>

#include "HttpRequest.h"

using namespace boost;
using namespace boost::asio::ip;

HttpRequest::HttpRequest(asio::io_context &io_ctx)
    : WebRequestAbstract{io_ctx},
      _socket{io_ctx}
{
}

// ! beast of a code, this is not good practice but for the sake of challenge I did it in this way.
void HttpRequest::async_ConnectAndGet(Url &url, std::string_view reqHeader)
{
    _resolver.async_resolve(url._host, "80",
                            [this, reqHeader](const system::error_code &ec, const tcp::resolver::results_type &res) {
                                // in case url resolving fails
                                if (ec.failed())
                                {
                                    std::cout << "Error on resolving: " << ec.message() << std::endl;
                                    return;
                                }

                                // use the obtained list of endpoints to connect
                                asio::async_connect(_socket, res,
                                                    [this, reqHeader](const system::error_code &ec, const tcp::endpoint &endpoint) {
                                                        // in case connection failes
                                                        if (ec.failed())
                                                        {
                                                            std::cout << "Error on connection: " << ec.message() << std::endl;
                                                            return;
                                                        }

                                                        // socket has sucessfully connected, send request header
                                                        asio::async_write(_socket, asio::buffer(reqHeader),
                                                                          [this](const system::error_code &ec, size_t snt_bytes) {
                                                                              // in case sending request header fails
                                                                              if (ec.failed())
                                                                              {
                                                                                  std::cout << "Error on sending request header: " << ec.message() << std::endl;
                                                                                  return;
                                                                              }

                                                                              // request header sucessfully sent, get the response from server
                                                                              std::shared_ptr<std::string> buf{new std::string{}};
                                                                              asio::async_read(_socket, asio::dynamic_buffer(*buf),
                                                                                               [buf](const system::error_code &ec, size_t recv_bytes) {
                                                                                                   // in case reading from socket failed
                                                                                                   if (ec.failed() && ec != asio::error::eof)
                                                                                                   {
                                                                                                       std::cout << "Error on receiving: " << ec.message() << std::endl;
                                                                                                       return;
                                                                                                   }

                                                                                                   // write response
                                                                                                   // std::cout << *buf << std::endl;

                                                                                               });
                                                                          });
                                                    });
                            });
}
void HttpRequest::Connect(Url &url)
{
    auto _endpoints = _resolver.resolve(url._host, url._scheme);
    _socket.set_option(tcp::no_delay(true));
    asio::connect(_socket, _endpoints);
}

std::string HttpRequest::Get(std::string_view reqHeader)
{
    boost::system::error_code ec;
    asio::write(_socket, asio::buffer(reqHeader), ec);

    if (ec.failed())
        std::cout << "Error on write header: " << ec.message() << std::endl;

    std::string temp;
    asio::read(_socket, asio::dynamic_buffer(temp), ec);
    return temp;
}

HttpRequest::~HttpRequest()
{
    _socket.close();
}