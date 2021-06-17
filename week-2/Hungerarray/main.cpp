#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>
#include <vector>
#include <boost/process.hpp>

#define REQ 10000
#define FD_LIM 1024

std::string beautify_duration(std::chrono::seconds input_seconds);

int main(int argv, char **argc)
{
    if (argv != 2)
    {
        std::cout << "./usuage url" << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<boost::process::child> process_pool;

    auto strt = std::chrono::high_resolution_clock::now();
    size_t req_count = REQ;
    while (req_count)
    {
        size_t strt = (req_count < FD_LIM) ? req_count : FD_LIM;
        process_pool.emplace_back(boost::process::child{"child", argc[1], std::to_string(strt)});
        req_count = ((req_count < FD_LIM)) ? 0 : req_count - FD_LIM;
    }

    std::for_each(process_pool.begin(), process_pool.end(), [](boost::process::child &proc) {
        if (proc.joinable())
            proc.wait();
    });

    auto duration = std::chrono::high_resolution_clock::now() - strt;

    std::cout << "Done in [" << beautify_duration(std::chrono::duration_cast<std::chrono::seconds>(duration)) << "]" << std::endl;

    return 0;
}

std::string beautify_duration(std::chrono::seconds input_seconds)
{
    using namespace std::chrono;
    typedef duration<int, std::ratio<86400>> days;
    auto d = duration_cast<days>(input_seconds);
    input_seconds -= d;
    auto h = duration_cast<hours>(input_seconds);
    input_seconds -= h;
    auto m = duration_cast<minutes>(input_seconds);
    input_seconds -= m;
    auto s = duration_cast<seconds>(input_seconds);

    auto dc = d.count();
    auto hc = h.count();
    auto mc = m.count();
    auto sc = s.count();

    std::stringstream ss;
    ss.fill('0');
    if (dc)
    {
        ss << d.count() << "d";
    }
    if (dc || hc)
    {
        if (dc)
        {
            ss << std::setw(2);
        } //pad if second set of numbers
        ss << h.count() << "h";
    }
    if (dc || hc || mc)
    {
        if (dc || hc)
        {
            ss << std::setw(2);
        }
        ss << m.count() << "m";
    }
    if (dc || hc || mc || sc)
    {
        if (dc || hc || mc)
        {
            ss << std::setw(2);
        }
        ss << s.count() << 's';
    }

    return ss.str();
}