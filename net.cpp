#include <boost/asio/io_service.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <array>
#include <string>
#include <iostream>
using namespace boost::asio;
using namespace boost::asio::ip;

namespace {
    io_service              io;
    tcp::resolver resolv   {io};
    tcp::socket tcp_socket {io};
    std::array<char, 4096> bytes;
}

void read_handler(const boost::system::error_code &ec, std::size_t nbytes)
{
    if (!ec) {
        std::cout.write(bytes.data(), nbytes);
        tcp_socket.async_read_some(buffer(bytes), read_handler);
    }
    exit(0);
}

void connect_handler(const boost::system::error_code &ec)
{
    if (!ec) {
        write(tcp_socket, buffer("GET / HTTP/1.1\r\n"
                                 "Host: theboostcpplibraries.com\r\n\r\n"));
        tcp_socket.async_read_some(buffer(bytes), read_handler);
    }
}

void resolve_handler(const boost::system::error_code &ec, tcp::resolver::iterator it)
{
    if (!ec)
        tcp_socket.async_connect(*it, connect_handler);
}

// Setup and initialize network.
void initnet()
{
    tcp::resolver::query q{"theboostcpplibraries.com", "80"};
    resolv.async_resolve(q, resolve_handler);
    io.run();
}
