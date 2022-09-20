#ifndef SERVERPROCESSOR_H
#define SERVERPROCESSOR_H

#include "IServerProcessor.h"

/**
 * @brief обработчик запросов/ответов от клиента
 */
class ServerProcessor : public IServerProcessor
{
    enum class json_parser
    {
        qt_json,
        boost_property_tree,
        boost_property_tree_qstring
    };
    const json_parser JSON_PARSER = json_parser::qt_json;

public:
    ServerProcessor() = default;

    virtual boost::beast::http::response<boost::beast::http::string_body>
    parseRequest(const boost::beast::http::request<boost::beast::http::string_body> &request) const override;
};

#endif // SERVERPROCESSOR_H
