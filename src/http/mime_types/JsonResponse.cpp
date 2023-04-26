/* SPDX-License-Identifier: Apache License 2.0
 *
 * Copyright(c) 2023 Andrey Borisovich. All rights reserved.
 *
 * Author: Andrey Borisovich <andrey@borisovich.com>
 */

#include <ServerCrud/http/mime_types/JsonResponse.hpp>
#include <ServerCrud/http/Response.hpp>
#include <ServerCrud/http/Status.hpp>
#include <memory>

namespace server_crud::http::mime_types
{

std::unique_ptr<server_crud::http::Response> JsonResponse::get_stock(server_crud::http::Status status) const
{
	return std::make_unique<JsonResponse>();
}

}