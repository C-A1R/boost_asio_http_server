#include "ServerProcessor.h"

#include "testJsonQt.h"
#include "testJsonBoost.h"
#include "testJsonBoostQString.h"

#include <boost/beast.hpp>

namespace beast = boost::beast;
namespace http = beast::http;

namespace my_program_state
{
    std::size_t request_count()
    {
        static std::size_t count = 0;
        return ++count;
    }

    char *now()
    {
        const std::time_t now = std::time(nullptr);
        return std::asctime(std::localtime(&now));
    }
}

http::response<http::string_body>
ServerProcessor::parseRequest(const http::request<http::string_body> &request) const
{
    http::response<http::string_body> response;
    response.version(request.version());
    response.keep_alive(true);

    switch (request.method())
    {
    case http::verb::get:
    {
        response.result(http::status::ok);
        response.set(http::field::server, "boost::asio server");
        if (request.target() == "/count")
        {
            sleep(10);
            response.set(http::field::content_type, "text/html");
            response.body() = std::string{"<html>\n"
                                              "<head><title>Request count</title></head>\n"
                                              "<body>\n"
                                                  "<h1>Request count</h1>\n"
                                                  "<p>There have been "}
                              + std::to_string(my_program_state::request_count()) +
                              std::string{" requests so far.</p>\n"
                                              "</body>\n"
                                          "</html>\n"};
            break;
        }
        else if (request.target() == "/time")
        {
            response.set(http::field::content_type, "text/html");
            response.body() = std::string{"<html>\n"
                                          "<head><title>Current time</title></head>\n"
                                              "<body>\n"
                                                  "<h1>Current time</h1>\n"
                                                  "<p>The current time is "}
                              + my_program_state::now() +
                              std::string{        "</p>\n"
                                              "</body>\n"
                                          "</html>\n"};
            break;
        }
        else
        {
            if (request.body().empty())
            {
                response.set(http::field::content_type, "text/plain");
                response.body() = "ok";
                break;
            }

            response.set(http::field::content_type, "application/json");
            if (JSON_PARSER == json_parser::qt_json)
            {
                response.body() = TestJsonQt::TestJson(request.body());
            }
            else if (JSON_PARSER == json_parser::boost_property_tree)
            {
                bool ok = true;
                response.body() = TestJsonBoost::TestJson(request.body(), ok);
                if (!ok)
                {
                    response.result(http::status::bad_request);
                    response.set(http::field::content_type, "text/plain");
                }
            }
            else if (JSON_PARSER == json_parser::boost_property_tree_qstring)
            {
                bool ok = true;
                response.body() = TestJsonBoostQString::TestJson(request.body(), ok);
                if (!ok)
                {
                    response.result(http::status::bad_request);
                    response.set(http::field::content_type, "text/plain");
                }
            }
            break;
        }
    }
    default:
    {
        response.result(http::status::bad_request);
        response.set(http::field::content_type, "text/plain");
        response.body() = "Invalid request-method '" + std::string(request.method_string()) + "'";
        break;
    }
    }

    return response;
}
