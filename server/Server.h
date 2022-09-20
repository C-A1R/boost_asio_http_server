#ifndef SERVER_H
#define SERVER_H

#include "boost/asio.hpp"

/**
 * @brief асинхронный сервер
 */
class Server
{
    boost::asio::ip::tcp::acceptor _acceptor;

public:
    Server(boost::asio::io_context& io_context, int port);
    void start();

private:
    void do_accept();
};

#endif //SERVER_H
