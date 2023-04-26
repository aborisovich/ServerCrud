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
#include <ServerCrud/http/Header.hpp>
#include <ServerCrud/http/Status.hpp>
#include <memory>
#include <boost/asio.hpp>
#include <string>
#include <vector>

namespace server_crud::http
{

/**
 * @brief Base class of HTTP response send to the Client.
*/
class Response
{
public:
    /**
     * @brief Sets HTTP status of this response.
     * @param status Status to set.
    */
    void set_status(Status status);

    /**
     * @brief Gets HTTP status of this response.
     * @return Current status.
    */
    Status get_status();

    /**
     * @brief Gets HTTP status of this response.
     * @return String description of current status.
    */
    std::string& get_status_desc();

    /**
     * @brief List of headers to be included in the response.
    */
    std::vector<Header> headers;

    /**
     * @brief Content send in the response.
    */
    std::string content;
    
    /**
     * @brief Convert the reply into a vector of buffers. The buffers do not own the
     * underlying memory blocks, therefore the reply object must remain valid and
     * not be changed until the write operation has completed.
     * @return Vector of not owning buffers containing response.
    */
    std::vector<boost::asio::const_buffer> to_buffers();

    /**
     * @brief Get a stock reply used during invalid operation requests.
     * @param status Status to be included in the stock response.
     * @return A stock response instance.
    */
    virtual std::unique_ptr<Response> get_stock(Status status) const = 0;

private:
    boost::asio::const_buffer to_buffer(Status status);

    /**
     * @brief HTTP status of the current response.
    */
    Status status {Status::INTERNAL_SERVER_ERROR};

    /**
     * @brief Placeholder for string representation of the status.
    */
    std::string status_desc;
};

}