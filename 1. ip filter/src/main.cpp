#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

using ipv4_addr_t       = std::vector<unsigned int>;
using ipv4_addr_pool_t  = std::vector<ipv4_addr_t>;
using splitted_string_t = std::vector<std::string>;


std::ostream& operator<<(std::ostream& out, const ipv4_addr_t& ip)
{
    for (auto cur = ip.begin(); cur != ip.end(); ++cur)
    {
        out << *cur;
        if (cur != ip.end()-1)
            std::cout << '.';
    }

    return out;
}

std::ostream& operator<<(std::ostream& out, const ipv4_addr_pool_t pool)
{
    for (auto cur = pool.begin(); cur != pool.end(); ++cur)
    {
        out << *cur;
        if (cur != pool.end()-1)
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
splitted_string_t split(const std::string &str, char delimeter)
{
    splitted_string_t res;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(delimeter);
    while(stop != std::string::npos)
    {
        res.push_back(str.substr(start, stop - start));
        start = stop + 1;
        stop = str.find_first_of(delimeter, start);
    }

    res.push_back(str.substr(start));
    return res;
}

ipv4_addr_pool_t get_ip_pool(std::istream& in)
{
    ipv4_addr_pool_t ip_pool;
    std::string ip_line;

    while(std::getline(in, ip_line))
    {
        // Get line of data: "target_ip\tTRASH\tTRASH\t"
        splitted_string_t tmp = split(ip_line, '\t');
        std::string ipv4_str = tmp.at(0);

        splitted_string_t octets = split(ipv4_str, '.');
        assert(octets.size() == 4);

        ipv4_addr_t ip;
        std::for_each(octets.begin(), octets.end(),
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

        ip_pool = get_ip_pool(std::cin);
        std::sort(ip_pool.begin(), ip_pool.end(), std::greater<ipv4_addr_t>());

        std::cout << ip_pool << std::endl;
        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8


        // Filter by first byte and output
        auto filter = [&ip_pool](auto ...args)
        {
            ipv4_addr_pool_t filtered{};
            ipv4_addr_t ip_mask{};

            // unpacking filter variadic parameters
            const int count_of_octets = sizeof...(args);
            static_assert(count_of_octets <= 4);

            int a[count_of_octets] = {
                (ip_mask.push_back(args), 0)...
            };

            for (auto &ip : ip_pool)
            {
                // check ip by mask
                if (std::equal(
                        ip_mask.begin(), ip_mask.begin()+count_of_octets,
                        ip.begin(), ip.begin()+count_of_octets))
                {
                    std::cout << ip << std::endl;
                }
            }
        };

        filter(1);
        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8


        filter(46, 70);
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76


        // TODO filter by any byte and output
        auto filter_any = [&ip_pool](int target_octet)
        {
            for (auto &ip : ip_pool)
            {
                if (std::any_of(ip.begin(), ip.end(),
                                [&](auto octet){return octet==target_octet;}))
                {
                    std::cout << ip << std::endl;
                }
            }
        };

        filter_any(46);
        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
