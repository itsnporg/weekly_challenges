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

// ! beast of a code, this is not good practice but for the sake of challenge I did it in this way.
void HttpRequest::async_ConnectAndGet(Url &url, std::string_view reqHeader)
{
    _resolver.async_resolve(url._host, "80",
                            [this, reqHeader](const system::error_code &ec, const tcp::resolver::results_type &res)
                            {
                                // in case url resolving fails
                                if (ec.failed())
                                {
                                    std::cout << "Error on resolving: " << ec.message() << std::endl;
                                    _socket.~basic_stream_socket();
                                    return;
                                }

                                // use the obtained list of endpoints to connect
                                asio::async_connect(_socket, res,
                                                    [this, reqHeader](const system::error_code &ec, const tcp::endpoint &endpoint)
                                                    {
                                                        // in case connection failes
                                                        if (ec.failed())
                                                        {
                                                            std::cout << "Error on connection: " << ec.message() << std::endl;
                                                            _socket.~basic_stream_socket();
                                                            return;
                                                        }

                                                        // socket has sucessfully connected, send request header
                                                        asio::async_write(_socket, asio::buffer(reqHeader),
                                                                          [this](const system::error_code &ec, size_t snt_bytes)
                                                                          {
                                                                              // in case sending request header fails
                                                                              if (ec.failed())
                                                                              {
                                                                                  std::cout << "Error on sending request header: " << ec.message() << std::endl;
                                                                                  _socket.~basic_stream_socket();
                                                                                  return;
                                                                              }

                                                                              // request header sucessfully sent, get the response from server
                                                                              std::shared_ptr<std::string> buf{new std::string{}};
                                                                              asio::async_read(_socket, asio::dynamic_buffer(*buf),
                                                                                               [this, buf](const system::error_code &ec, size_t recv_bytes)
                                                                                               {
                                                                                                   // in case reading from socket failed
                                                                                                   if (ec.failed() && ec != asio::error::eof)
                                                                                                   {
                                                                                                       std::cout << "Error on receiving: " << ec.message() << std::endl;
                                                                                                       _socket.~basic_stream_socket();
                                                                                                       return;
                                                                                                   }
                                                                                                   _socket.~basic_stream_socket();
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

void HttpRequest::benchmark(Url &url, std::string reqHeader)
{
    
    _reqHeader = reqHeader;
    _resolver.async_resolve(url._host, url._scheme,
                            boost::bind(&HttpRequest::handle_resolve, this, boost::asio::placeholders::error, boost::asio::placeholders::iterator));
}

void HttpRequest::handle_resolve(const system::error_code &er, tcp::resolver::results_type endpoints)
{
    if (er.failed())
    {
        std::cout << "Resolve failed: " << er.message() << std::endl;
        return;
    }
    asio::async_connect(_socket, endpoints,
                        boost::bind(&HttpRequest::handle_connect, this, boost::asio::placeholders::error, boost::asio::placeholders::endpoint));
}

void HttpRequest::handle_connect(const system::error_code &er, tcp::endpoint endpoint)
{
    if (er.failed())
    {
        std::cout << "Connect failed: " << er.message() << std::endl;
        return;
    }
    asio::async_write(_socket, asio::buffer(_reqHeader),
                      boost::bind(&HttpRequest::handle_write, this, boost::asio::placeholders::error, ::asio::placeholders::bytes_transferred));
}

void HttpRequest::handle_write(const system::error_code &er, size_t snt)
{
    if (er.failed())
    {
        std::cout << "write failed" << er.message() << std::endl;
        return;
    }
    std::shared_ptr<std::string> buf{new std::string};
    asio::async_read(_socket, asio::dynamic_buffer(*buf),
                     boost::bind(&HttpRequest::handle_read, this, buf, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void HttpRequest::handle_read(std::shared_ptr<std::string> response, const system::error_code &er, size_t recv)
{
    if (er.failed())
    {
        std::cout << "read failed: " << er.message() << std::endl;
        return;
    }

    std::cout << *response << std::endl;

    if (++count != reqCount)
    {
        asio::async_write(_socket, asio::buffer(_reqHeader),
                          boost::bind(&HttpRequest::handle_write, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }
}
HttpRequest::~HttpRequest()
{
    if (_socket.is_open())
        _socket.~basic_stream_socket();
}