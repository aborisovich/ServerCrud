/* SPDX-License-Identifier: Boost Software License 1.0
 *
 * Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
 * 
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
#include <ServerCrud/http/Request.hpp>
#include <ServerCrud/http/RequestParser.hpp>
#include <ServerCrud/http/IRequestHandler.hpp>
#include <ServerCrud/http/Response.hpp>
#include <memory>
#include <array>
#include <boost/asio.hpp>

namespace server_crud::http
{

/**
 * @brief Represents a single connection from a client.
*/
class Connection final : public std::enable_shared_from_this<Connection>
{
public:
    /**
     * @brief Construct a connection with the given io_service.
     * @param io_service 
     * @param request_handler 
    */
    explicit Connection(boost::asio::io_context& io_service, IRequestHandler& request_handler);

    /**
     * @brief Start the first asynchronous operation for the connection.
    */
    void start();

    /**
     * @brief Get the socket associated with the connection.
     * @return 
    */
    boost::asio::ip::tcp::socket& get_socket();

private:
    /**
     * @brief Handle completion of a read operation.
     * @param e Error.
     * @param bytes_transferred 
    */
    void handle_read(const boost::system::error_code& e,
        std::size_t bytes_transferred);

    /**
     * @brief Handle completion of a write operation.
     * @param e Error.
    */
    void handle_write(const boost::system::error_code& e);

    /**
     * @brief Strand to ensure the connection's handlers are not called concurrently.
    */
    boost::asio::io_context::strand strand;

    /**
     * @brief Socket for the connection.
    */
    boost::asio::ip::tcp::socket socket;

    /**
     * @brief The handler used to process the incoming request.
    */
    IRequestHandler& request_handler;

    /**
     * @brief Buffer for incoming data.
    */
    std::array<char, 8192> buffer;

    /**
     * @brief  The incoming request.
    */
    Request request;

    /**
     * @brief The parser for the incoming request.
    */
    RequestParser request_parser;

    /**
     * @brief The response to be sent back to the client.
    */
    std::unique_ptr<Response> response;
};

}
