#include <sstream>
#include <algorithm>
#include <boost/asio/thread_pool.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/process.hpp>

#include "Connect.h"
#include "HttpRequest.h"
#include "HttpsRequest.h"

using boost::asio::ip::tcp;

boost::asio::io_context Connect::_io_context;

Connect::Connect(const Url &url)
    : _url{url},
      _request_header{Create_request_header(url._host, url._path)},
      _thread_pool{5}
{
}

std::string Connect::Create_request_header(std::string_view host, std::string_view path)
{
    std::stringstream ss;
    ss << "GET " << path << " HTTP/1.1\r\n"
       << "Host: " << host << "\r\n"
       << "Accept: text/html\r\n"
       << "User-Agent: Mozilla/5.0\r\n"
       << "\r\n";

    return ss.str();
}

void Connect::Start(size_t num)
{

}

void Connect::HitRequest(size_t lim)
{
    WebRequest req{new HttpRequest{_io_context}};
    req->Connect(_url);


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
