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

#pragma once
#include <boost/asio.hpp>
#include <ServerCrud/http/Connection.hpp>
#include <memory>
#include <string>
#include <vector>
#include <string_view>

namespace server_crud
{

/**
 * @brief Construct the server to listen on the specified TCP address and port.
 * Uses thread pool implementation - each new connection is managed by the new thread.
*/
class ServerCrud final
{
public:
    /**
     * @brief Constructs a ServerCrud instance.
     * @param address IP address (IPv4 or IPv6) that Server will run on.
     * @param tcp_port Number of TCP port to listen on.
     * @param thread_pool_size Maximal number of threads used to handle network requests.
     * @param request_handler Specialized for given MIME type content request handler.
    */
    ServerCrud(const std::string& address, unsigned short tcp_port, std::size_t thread_pool_size,
        std::unique_ptr<http::IRequestHandler> request_handler);
    ServerCrud(const ServerCrud& other) = delete;

    /**
     * @brief 
     * @param other 
    */
    ServerCrud(ServerCrud&& other) = delete;
    ServerCrud& operator=(const ServerCrud& other) = delete;
    ServerCrud& operator=(ServerCrud&& other) = delete;
    ~ServerCrud();

    /**
     * @brief Two ServerCrud instances are equal, when their address and tcp_port
     * have equal values.
     * @param rhs ServerCrud instance to compare to.
     * @return True when instances are qeual.
    */
    bool operator==(const ServerCrud& rhs) const;

    /**
     * @brief Starts the server.
    */
    void run();

    /**
     * @brief Stops the server.
    */
    void stop();

    inline const std::string& get_ip_address() const { return address; }

    inline unsigned short get_tcp_port() const { return tcp_port; }

    /**
     * @brief List of created ServerCrud instances.
     * Each of the is running on different IP address and TCP port.
    */
    static std::vector<std::reference_wrapper<ServerCrud>> server_instances;

private:
    /**
     * @brief Handle completion of an asynchronous accept operation.
     * @param[out] e Output error code.
    */
    void handle_accept(const boost::system::error_code& e);

    /**
     * @brief IP address of the server instance.
    */
    const std::string address;

    /**
     * @brief TCP port number that server will listen requests on.
    */
    unsigned short tcp_port;

    /**
     * @brief The number of threads that will call io_service::run().
    */
    std::size_t thread_pool_size;

    /**
     * @brief The io_service used to perform asynchronous operations.
    */
    boost::asio::io_context io_service;

    /**
     * @brief Acceptor used to listen for incoming connections.
    */
    boost::asio::ip::tcp::acceptor acceptor;

    /**
     * @brief The next connection to be accepted.
    */
    std::shared_ptr<http::Connection> connection;

    /**
     * @brief The handler for all incoming requests.
    */
    std::unique_ptr<http::IRequestHandler> request_handler;
};

}
