#include <sstream>
#include <algorithm>

#include "Connect.h"
#include "HttpRequest.h"
#include "HttpsRequest.h"

using boost::asio::ip::tcp;

boost::asio::io_context Connect::_io_context;

Connect::Connect(const Url &url)
    : _url{url},
      _request_header{Create_request_header(url._host, url._path)}
{
}

std::string Connect::Create_request_header(std::string_view host, std::string_view path)
{
    std::stringstream ss;
    ss << "GET " << path << " HTTP/1.1\r\n"
       << "Host: " << host << "\r\n"
       << "Accept: text/html\r\n"
       << "User-Agent: Mozilla/5.0\r\n"
       << "Connection: close\r\n"
       << "\r\n";

    return ss.str();
}

void Connect::Start(size_t num)
{
    for (size_t i = 0; i < num; ++i)
    {
        _webRequests.emplace_back(Create_WebRequest());
        _webRequests.back()->async_ConnectAndGet(_url, _request_header);
    }
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
    auto &ctx = _io_context;
    size_t available_threads = std::thread::hardware_concurrency();
    for (size_t i = 0; i != available_threads; ++i)
    {
        _thread_pool.emplace_back(std::thread{[&ctx]() {
            ctx.run();
        }});
    }
    _io_context.run();

    std::for_each(_thread_pool.begin(), _thread_pool.end(), [](std::thread &thrd) {
        if(thrd.joinable())
            thrd.join();
    });
}
