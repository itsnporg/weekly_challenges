#include <sstream>

#include "Connect.h"

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