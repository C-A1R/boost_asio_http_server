#ifndef ISERVERPROCESSOR_H
#define ISERVERPROCESSOR_H

#include <boost/beast/http.hpp>

#include <string>

/**
 * @brief интерфейс обработчика запросов/ответов от клиента
 */
class IServerProcessor
{
public:
    IServerProcessor() = default;
    virtual ~IServerProcessor() = default;

    virtual boost::beast::http::response<boost::beast::http::string_body>
    parseRequest(const boost::beast::http::request<boost::beast::http::string_body> &request) const = 0;
};

#endif // ISERVERPROCESSOR_H
