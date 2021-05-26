#include <iostream>
#include <string>

#include "asio.hpp"
#include "asio/ssl.hpp"

template <typename Verifier>
class verbose_verification
{
public:
    verbose_verification(Verifier verifier)
        : verifier_(verifier)
    {
    }

    bool operator()(
        bool preverified,
        asio::ssl::verify_context &ctx)
    {
        char subject_name[256];
        X509 *cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
        X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
        bool verified = verifier_(preverified, ctx);
        std::cout << "Verifying: " << subject_name << "\n"
                                                      "Verified: "
                  << verified << std::endl;
        return verified;
    }

private:
    Verifier verifier_;
};

///@brief Auxiliary function to make verbose_verification objects.
template <typename Verifier>
verbose_verification<Verifier>
make_verbose_verification(Verifier verifier)
{
    return verbose_verification<Verifier>(verifier);
}

bool on_peer_verify(bool preverified, asio::ssl::verify_context &context)
{
    return true;
}

int main(int argc, char **argv)
{
    if (argc < 1)
    {
        std::cout << "not enough arguments" << std::endl;
        return 1;
    }
    std::string host{argv[1]};
    asio::io_context io_context;

    asio::ip::tcp::resolver resolver{io_context};
    asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, "https");

    //asio::ip::tcp::socket socket(io_context);
    //asio::connect(socket, endpoints);

    asio::ssl::context ctx{asio::ssl::context::sslv23_client};
    ctx.add_verify_path("/etc/ssl/certs/");
    ctx.set_default_verify_paths();

    asio::ssl::stream<asio::ip::tcp::socket> ssl_sock{io_context, ctx};
    SSL_set_tlsext_host_name(ssl_sock.native_handle(), host.c_str());

    auto &sock = ssl_sock.lowest_layer();
    sock.connect(*endpoints.begin());
    // ssl_sock.lowest_layer().set_option(asio::ip::tcp::no_delay(true));

    ssl_sock.set_verify_mode(asio::ssl::verify_peer);
    ssl_sock.set_verify_callback(
        /* [](bool preverified, asio::ssl::verify_context& context) -> bool{
		return on_peer_verify(preverified, context);
		} */
        make_verbose_verification(
            asio::ssl::rfc2818_verification(host)));

    ssl_sock.handshake(asio::ssl::stream<asio::ip::tcp::socket>::client);

    std::string request{
        "GET / HTTP/1.1\r\n"
        "Host: "};

    request += host;
    request += std::string{
        "\r\n"
        "Accept: text/html\r\n"
        "User-Agent: Mozilla/5.0\r\n"
        "Connection: close\r\n"
        "\r\n"};

    std::cout << request << std::endl;

    asio::error_code ignored_error;
    asio::write(ssl_sock, asio::buffer(request), ignored_error);

    for (;;)
    {
        char buf[128];
        asio::error_code error;

        size_t len = ssl_sock.read_some(asio::buffer(buf), error);

        if (error)
            break;

        std::cout.write(buf, len);
    }

    return 0;
}
