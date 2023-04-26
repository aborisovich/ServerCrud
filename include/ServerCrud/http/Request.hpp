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
#include <string>
#include <vector>

namespace server_crud::http
{

/**
 * @brief HTTP request received from the Client.
*/
struct Request
{
	std::string method;
	std::string uri;
	int http_version_major;
	int http_version_minor;
	std::vector<Header> headers;
};

}