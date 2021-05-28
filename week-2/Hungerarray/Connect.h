#pragma once

#include <string>
#include <string_view>
#include <iostream>
#include <list>
#include <boost/asio.hpp>

#include "WebRequestAbstract.h"
#include "Url.h"

class Connect
{
public:
    static boost::asio::io_context _io_context;

public:
    Connect(const Url &url);

    // Start will start asynchronously given no. of connections
    void Start(size_t num);

    // Wait will wait for all he asynchronous task to end
    void Wait();

private:
    std::string Create_request_header(std::string_view host, std::string_view path);

private:
    Url _url;
    std::list<WebRequest> _webRequests;
    std::string _request_header;
};