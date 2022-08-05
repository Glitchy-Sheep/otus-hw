#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include <range/v3/all.hpp>

using ipv4_addr_t       = std::vector<unsigned int>;
using ipv4_addr_pool_t  = std::vector<ipv4_addr_t>;
using splitted_string_t = std::vector<std::string>;

std::ostream& operator<<(std::ostream& out, const ipv4_addr_t& ip)
{
    auto beg = ip.begin();
    auto end = ip.end();

    for (auto cur = beg; cur != end; ++cur)
    {
        out << *cur;
        if (cur != end-1)
            std::cout << '.';
    }

    return out;
}

std::ostream& operator<<(std::ostream& out, const ipv4_addr_pool_t pool)
{
    auto beg = pool.begin();
    auto end = pool.end();

    for (auto cur = beg; cur != end; ++cur)
    {
        out << *cur;
        if (cur != end-1)
            std::cout << '\n';
    }

    return out;
}

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
splitted_string_t split(const std::string &str, char d)
{
    splitted_string_t res;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        res.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    res.push_back(str.substr(start));

    return res;
}

ipv4_addr_pool_t get_ip_pool(std::istream& in)
{
    ipv4_addr_pool_t ip_pool;

    for(std::string line; std::getline(in, line);)
    {
        // Get line of data: "TARGET\tTRASH\tTRASH\t"
        splitted_string_t tmp = split(line, '\t');
        std::string ipv4_str = tmp.at(0);

        // ["255", "255", "255", "255"]
        splitted_string_t octets = split(ipv4_str, '.');
        assert(octets.size() == 4);

        // [255, 255, 255, 255]
        ipv4_addr_t ip;
        ranges::for_each(octets,
            [&ip](std::string octet)
            {
                ip.push_back(std::stoi(octet));
            }
        );

        ip_pool.push_back(ip);
    }

    return ip_pool;
}


int main(int argc, char const *argv[])
{
    try
    {
        ipv4_addr_pool_t ip_pool;
        ipv4_addr_pool_t sorted_pool;

        ip_pool = get_ip_pool(std::cin);
        ranges::sort(ip_pool, std::greater<ipv4_addr_t>());

        std::cout << ip_pool << std::endl;

        // filter(1)
        ranges::for_each(ip_pool, [](auto ip){
            if (ip.at(0) == 1)
                std::cout << ip << std::endl;
        });

        // filter(46, 70)
        ranges::for_each(ip_pool, [](auto ip){
            if (ip.at(0) == 46 && ip.at(1) == 70)
                std::cout << ip << std::endl;
        });

        ranges::for_each(ip_pool, [](auto ip){
            if (ranges::any_of(ip, [](auto octet){ return (octet == 46); }))
                std::cout << ip << std::endl;
        });
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}