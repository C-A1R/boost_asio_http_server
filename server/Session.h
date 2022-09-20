#ifndef SESSION_H
#define SESSION_H

#include "boost/asio.hpp"
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>

#include "server_processor/ServerProcessor.h"

/**
 * @brief сессия пользователя
 */
class Session : public std::enable_shared_from_this<Session>
{
    enum {max_length = 8192};

    boost::asio::ip::tcp::socket _socket;
    std::unique_ptr<IServerProcessor> _processor;
    boost::beast::flat_buffer _buffer{max_length};
    boost::beast::http::request<boost::beast::http::string_body> _request;
    boost::beast::http::response<boost::beast::http::string_body> _response;

public:
    Session(boost::asio::ip::tcp::socket socket, std::unique_ptr<IServerProcessor> processor);
    void start();

private:
    void do_read();
    void do_write();
};

#endif //SESSION_H
