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

#include <ServerCrud/http/Connection.hpp>
#include <functional>
#include <vector>
#include <optional>
#include <tuple>

namespace server_crud::http
{

Connection::Connection(boost::asio::io_context& io_service, IRequestHandler& request_handler) :
	strand(io_service),
	socket(io_service),
	request_handler(request_handler)
{}

void Connection::start()
{
	socket.async_read_some(boost::asio::buffer(buffer),
	  strand.wrap(
		  std::bind(&Connection::handle_read, shared_from_this(),
			  std::placeholders::_1,
			  std::placeholders::_2)));
}

boost::asio::ip::tcp::socket& Connection::get_socket()
{
	return socket;
}

void Connection::handle_read(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    // If an error occurs then no new asynchronous operations are started. This
    // means that all shared_ptr references to the connection object will
    // disappear and the object will be destroyed automatically after this
    // handler returns. The connection class's destructor closes the socket.
    if(error)
        return;

    std::optional<bool> result;
    std::tie(result, std::ignore) = request_parser.parse(request, buffer.data(), buffer.data() + bytes_transferred);

    if(result.has_value())
    {
        if(result.value())
        {
            response = request_handler.handle_request(request);
            boost::asio::async_write(socket, response->to_buffers(),
                strand.wrap(
                    std::bind(&Connection::handle_write, shared_from_this(),
                        std::placeholders::_1)));
        }
        else
        {
            response = request_handler.get_default_response(Status::BAD_REQUEST);
            boost::asio::async_write(socket, response->to_buffers(),
                strand.wrap(
                    std::bind(&Connection::handle_write, shared_from_this(),
                        std::placeholders::_1)));
        }
    }
    else
    {
        socket.async_read_some(boost::asio::buffer(buffer),
            strand.wrap(
                std::bind(&Connection::handle_read, shared_from_this(),
                    std::placeholders::_1,
                    std::placeholders::_2)));
    }
}
void Connection::handle_write(const boost::system::error_code & e)
{
    if(!e)
    {
        // Initiate graceful connection closure.
        boost::system::error_code ignored_ec;
        socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
    }

    // No new asynchronous operations are started. This means that all shared_ptr
    // references to the connection object will disappear and the object will be
    // destroyed automatically after this handler returns. The connection class's
    // destructor closes the socket.
}

}