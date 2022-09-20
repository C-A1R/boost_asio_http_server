#include "Server.h"

#include "Session.h"
#include "server_processor/ServerProcessor.h"

using boost::asio::ip::tcp;

Server::Server(boost::asio::io_context& io_context, int port)
    : _acceptor{io_context, tcp::endpoint(tcp::v4(), port)}
{
}

void Server::start()
{
    do_accept();
}

void Server::do_accept()
{
    _acceptor.async_accept([this](const boost::system::error_code &ec, tcp::socket socket)
    {
        if (!ec)
        {
            auto session = std::make_shared<Session>(std::move(socket), std::make_unique<ServerProcessor>());
            session->start();
        }
        do_accept();
    });
}
