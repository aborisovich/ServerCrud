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

#include <iostream>
#include <format>
#include <sstream>

namespace server_crud::http
{

/**
 * @brief Some HTTP protocol status codes defined by the protocol standard
 * rfc9110: https://datatracker.ietf.org/doc/html/rfc9110
*/
enum class Status : unsigned short
{
    OK = 200,
    CREATED = 201,
    ACCEPTED = 202,
    NO_CONTENT = 204,
    MULTIPLE_CHOICES = 300,
    MOVED_PERNAMENTLY = 301,
    MOVED_TEMPORARILY = 302,
    NOT_MODIFIED = 304,
    BAD_REQUEST = 400,
    UNAUTHORISED = 401,
    FORBIDDEN = 403,
    NOT_FOUND = 404,
    INTERNAL_SERVER_ERROR = 500,
    NOT_IMPLEMENTED = 501,
    BAD_GATEWAY = 502,
    SERVICE_UNAVAILABLE = 503
};

/**
 * @brief Returns descriptive HTTP status code names.
 * @param stream Output stream.
 * @param status Status to convert.
*/
std::ostream& operator<<(std::ostream& stream, const Status& status);

/**
 * @brief Converts HTTP Status to string.
 * @param status status to convert.
 * @return string representation of the HTTP status.
*/
std::string to_string(const Status& status);

}
