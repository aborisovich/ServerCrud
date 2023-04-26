/* SPDX-License-Identifier: Boost Software License 1.0
 *
 * Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 * Author: Christopher M. Kohlhoff
 */

/* SPDX-License-Identifier: Apache License 2.0
 *
 * Copyright(c) 2023 Andrey Borisovich. All rights reserved.
 *
 * Author: Andrey Borisovich <andrey@borisovich.com>
 */

#include <ServerCrud/ServerCrud.hpp>
#include <memory>
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>
#include <thread>
#include <format>

namespace server_crud
{

std::vector<std::reference_wrapper<ServerCrud>> ServerCrud::server_instances {};

ServerCrud::ServerCrud(const std::string& address, unsigned short tcp_port, std::size_t thread_pool_size,
    std::unique_ptr<http::IRequestHandler> request_handler)
    : address(address),
    tcp_port(tcp_port),
    thread_pool_size(thread_pool_size),
    acceptor(io_service),
    connection(std::make_shared<server_crud::http::Connection>(io_service, *request_handler.get())),
    request_handler(std::move(request_handler))
{
    if(!server_instances.empty())
        for(auto& instance : server_instances)
        {
            if(*this == instance)
                throw std::runtime_error("Unable to create server instance. Instance with similar network address exists.");
        }

    boost::asio::ip::address ip_address = boost::asio::ip::make_address(address);
    boost::asio::ip::tcp::endpoint endpoint {ip_address, tcp_port};
    std::cout << std::format("Starting new server at IP: {} TCP port: {}", endpoint.address().to_string(), endpoint.port()) << std::endl;
    acceptor.open(endpoint.protocol());
    acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor.bind(endpoint);
    acceptor.listen();
    acceptor.async_accept(connection->get_socket(),
        std::bind(&ServerCrud::handle_accept, this,
            std::placeholders::_1));

    server_instances.emplace_back(*this);
}

ServerCrud::~ServerCrud()
{
    try
    {
        if(!io_service.stopped())
            io_service.stop();
        std::erase(server_instances, *this);
    }
    catch(...)
    { }
}

bool ServerCrud::operator==(const ServerCrud& rhs) const
{
    return (address == rhs.address &&
        tcp_port == rhs.tcp_port);
}

void ServerCrud::run()
{
    // Create a pool of threads to run all of the io_services.
    std::vector<std::shared_ptr<std::thread>> threads;
    for(std::size_t i = 0; i < thread_pool_size; ++i)
    {
        std::shared_ptr<std::thread> thread = std::make_shared<std::thread>(
            [this]{ io_service.run(); });
        threads.push_back(thread);
    }

    // Wait for all threads in the pool to exit.
    for(std::size_t i = 0; i < threads.size(); ++i)
        threads[i]->join();
}

void ServerCrud::stop()
{
    io_service.stop();
}

void ServerCrud::handle_accept(const boost::system::error_code& e)
{
    if(!e)
    {
        connection->start();
        connection.reset(new http::Connection(io_service, *request_handler.get()));
        boost::asio::ip::tcp::socket& socket = connection.get()->get_socket();
        acceptor.async_accept(socket,
            std::bind(&ServerCrud::handle_accept, this,
                std::placeholders::_1));
    }
}
}