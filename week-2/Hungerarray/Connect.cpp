#include <sstream>
#include <algorithm>

#include "Connect.h"
#include "HttpRequest.h"

using boost::asio::ip::tcp;

boost::asio::io_context Connect::_io_context;

Connect::Connect(const Url &url)
    : _request_header{Create_request_header(url._host, url._path)},
      _resolver{_io_context},
      _endpoints{_resolver.resolve(url._host, url._scheme)}
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
        std::cout << "Making new HttpRequest" << std::endl;
        _webRequests.emplace_back(new HttpRequest{_io_context});
    }

    for (auto &webReq : _webRequests)
    {
        webReq->Connect(_endpoints);
        std::string temp {webReq->Get(_request_header)};
        std::cout << temp << std::endl;
    }
}

void Connect::Wait()
{
    auto taskCompleted = _io_context.run();
    std::cout << "Task Completed: " << taskCompleted << std::endl;
}
