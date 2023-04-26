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
#include <ServerCrud/http/Response.hpp>
#include <ServerCrud/http/mime_types/JsonResponse.hpp>
#include <memory>

namespace server_crud::http
{

class IRequestHandler
{
public:
	virtual std::unique_ptr<Response> handle_request(const Request& req) = 0;
	virtual std::unique_ptr<Response> get_default_response(Status status) = 0;
	virtual ~IRequestHandler() = default;
};

}