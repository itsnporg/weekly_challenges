#include <iostream>
#include <thread>
#include <boost/asio/thread_pool.hpp>
#include <boost/asio/io_context.hpp>

#include "Connect.h"
#include "HttpRequest.h"
#include "HttpsRequest.h"

using boost::asio::ip::tcp;

boost::asio::io_context Connect::_io_context;

Connect::Connect(const Url &url)
    : _url{url},
      _request_header{Create_request_header(url._host, url._path, false)},
      _req_persist_header{Create_request_header(url._host, url._path, true)},
      _thread_pool{17}
{
}

std::string Connect::Create_request_header(std::string_view host, std::string_view path, bool persistent)
{
    std::stringstream ss;
    ss << "GET " << path << " HTTP/1.1\r\n"
       << "Host: " << host << "\r\n"
       << "Accept: text/html\r\n"
       << "User-Agent: Mozilla/5.0\r\n";
    if (!persistent)
        ss << "Connection: close\r\n";

    ss << "\r\n";

    return ss.str();
}

void Connect::Start(size_t num)
{
    // if evenly divisible by 16, then it will create and use 16 sockets, else will create and use 17 sockets
    constexpr size_t no_of_sockets = 16;
    const size_t req_per_socket = num / no_of_sockets;

    size_t i;
    for (i = 0; req_per_socket && i < no_of_sockets - 1; ++i)
    {
        Create_request(i, req_per_socket);
    }
    size_t lim = num - req_per_socket * (no_of_sockets - 1);
    Create_request(i, lim);
}

void Connect::Create_request(size_t socketNo, size_t lim)
{
    _webRequests.emplace_back(Create_WebRequest());
    // std::cout << "Socket " << socketNo << " starting " << lim << " Requests" << std::endl;
    boost::asio::post(_thread_pool, [socketNo, &url = _url, &Req = _req_persist_header, &endReq = _request_header, lim, &web = _webRequests.back()]()
                      {
                          web->async_Connect(url).get();
                          std::string response = web->async_Get_pipeline(Req, endReq, lim).get();
                      });
}

WebRequest Connect::Create_WebRequest()
{
    if (_url._scheme == "http")
        return WebRequest{new HttpRequest{_io_context}};
    else
        return WebRequest{new HttpsRequest{_io_context}};
}

void Connect::Wait()
{
    _thread_pool.join();
}
