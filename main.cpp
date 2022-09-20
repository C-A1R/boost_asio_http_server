#include <iostream>

#include "server/Server.h"

int main()
{
    try
    {
        int port = 9000;
        std::cout << "RUN_SERVER / port: " << port << std::endl;

        const int threads = std::thread::hardware_concurrency();
        boost::asio::io_context io_context;
        Server server(io_context, port);
        server.start();
        std::vector<std::thread> v;
        v.reserve(threads - 1);
        for (auto i = threads - 1; i > 0; --i)
        {
            v.emplace_back([&io_context]()
            {
                io_context.run();
            });
        }
        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "ERR server not started: " << e.what() << std::endl;
    }

    return 0;
}

