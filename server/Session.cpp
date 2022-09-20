#include "Session.h"

namespace beast = boost::beast;
namespace http = beast::http;

Session::Session(boost::asio::ip::tcp::socket socket, std::unique_ptr<IServerProcessor> processor)
    : _socket{std::move(socket)}, _processor{std::move(processor)}
{
}

void Session::start() 
{
    if (!_processor)
    {
        return;
    }
    do_read();
}

void Session::do_read() 
{
    auto self{shared_from_this()};
    http::async_read(_socket, _buffer, _request, [self](const beast::error_code &ec, const std::size_t /*length*/)
    {
        if (!ec)
        {
            self->_response = self->_processor->parseRequest(self->_request);
            self->do_write();
        }
    });
}

void Session::do_write()
{
    _response.content_length(_response.body().size());
    auto self{shared_from_this()};
    http::async_write(_socket, _response, [self](const beast::error_code &ec, const std::size_t /*length*/)
    {
        if (!ec)
        {
            self->_request = http::request<http::string_body>();//clear
            self->do_read();
        }
    });
}

