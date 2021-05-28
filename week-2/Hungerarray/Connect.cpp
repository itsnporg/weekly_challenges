#include <sstream>
#include <algorithm>

#include "Connect.h"
#include "HttpRequest.h"

using boost::asio::ip::tcp;

boost::asio::io_context Connect::_io_context;

Connect::Connect(const Url &url)
    : _url{url},
      _request_header{Create_request_header(url._host, url._path)}
{
    std::cout << "Endpoints Setup Complete" << std::endl;
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
        _webRequests.emplace_back(new HttpRequest{_io_context});
        _webRequests.back()->async_ConnectAndGet(_url, _request_header);
    }
}

void Connect::Wait()
{
    auto taskCompleted = _io_context.run();
    std::cout << "Task Completed: " << taskCompleted << std::endl;
}
