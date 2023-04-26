/* SPDX-License-Identifier: Apache License 2.0
 *
 * Copyright(c) 2023 Andrey Borisovich. All rights reserved.
 *
 * Author: Andrey Borisovich <andrey@borisovich.com>
 */

#include <ServerCrud/http/mime_types/JsonRequestHandler.hpp>
#include <ServerCrud/http/mime_types/JsonResponse.hpp>
#include <memory>

namespace server_crud::http::mime_types
{

std::unique_ptr<server_crud::http::Response> JsonRequestHandler::handle_request(const server_crud::http::Request& req)
{
	std::cout << "Handling request\n";
	return std::make_unique<JsonResponse>();
}

std::unique_ptr<server_crud::http::Response> JsonRequestHandler::get_default_response(server_crud::http::Status status)
{
	std::cout << "Handling default request\n";
	return std::make_unique<JsonResponse>()->get_stock(status);
}

}