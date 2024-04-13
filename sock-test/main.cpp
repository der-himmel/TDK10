#include <iostream>
#include <thread>
#include "server.cpp" // Include the server code
#include "client.cpp" // Include the client code

void start_server(short port) {
    boost::asio::io_context io_context;
    server s(io_context, port);
    io_context.run();
}

void start_client(const std::string& host, const std::string& port, const std::string& message) {
    boost::asio::io_context io_context;
    client c(io_context, host, port);
    c.write(message);
    c.close();
}

int main() {
    const std::string host = "127.0.0.1";
    const std::string port = "1111";
    const std::string message = "THIS IS A TEST MESSAGE";

    // Start server in a separate thread
    std::thread server_thread(start_server, std::stoi(port));

    // Give the server a moment to start up
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Start client in a separate thread
    std::thread client_thread(start_client, host, port, message);

    // Wait for the server and client to finish
    client_thread.join();
    server_thread.join();

    return 0;
}
