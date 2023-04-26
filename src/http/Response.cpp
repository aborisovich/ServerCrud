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

#include <ServerCrud/http/Response.hpp>

namespace server_crud::http
{

std::vector<boost::asio::const_buffer> Response::to_buffers()
{
    std::vector<boost::asio::const_buffer> buffers;
    buffers.push_back(to_buffer(status));
    for(std::size_t i = 0; i < headers.size(); ++i)
    {
        Header& header = headers[i];
        buffers.push_back(boost::asio::buffer(header.name));
        buffers.push_back(boost::asio::buffer(Header::name_value_separator));
        buffers.push_back(boost::asio::buffer(header.value));
        buffers.push_back(boost::asio::buffer(Header::crlf));
    }
    buffers.push_back(boost::asio::buffer(Header::crlf));
    buffers.push_back(boost::asio::buffer(content));
    return buffers;
}

boost::asio::const_buffer Response::to_buffer(Status status)
{
    return boost::asio::const_buffer(status_desc.c_str(), status_desc.size());
}

void Response::set_status(Status status)
{
    status = status;
    status_desc = to_string(status);
}

Status Response::get_status()
{
    return status;
}

std::string& Response::get_status_desc()
{
    return status_desc;
}


}