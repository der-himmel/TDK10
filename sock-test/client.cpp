#include <boost/asio.hpp>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

class client {
public:
    client(boost::asio::io_context& io_context, const std::string& host, const std::string& port)
        : io_context_(io_context),
        socket_(io_context) {
        connect(host, port);
    }

    void write(const std::string& message) {
        boost::asio::write(socket_, boost::asio::buffer(message));
    }

    void close() {
        io_context_.stop();
        socket_.close();
    }

private:
    void connect(const std::string& host, const std::string& port) {
        tcp::resolver resolver(io_context_);
        boost::asio::connect(socket_, resolver.resolve(host, port));
    }

    boost::asio::io_context& io_context_;
    tcp::socket socket_;
};
