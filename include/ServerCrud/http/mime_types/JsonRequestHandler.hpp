/* SPDX-License-Identifier: Apache License 2.0
 *
 * Copyright(c) 2023 Andrey Borisovich. All rights reserved.
 *
 * Author: Andrey Borisovich <andrey@borisovich.com>
 */

#pragma once
#include <ServerCrud/http/IRequestHandler.hpp>
#include <ServerCrud/http/mime_types/JsonResponse.hpp>

namespace server_crud::http::mime_types
{

class JsonRequestHandler final : public server_crud::http::IRequestHandler
{
public:
	virtual std::unique_ptr<server_crud::http::Response> handle_request(const server_crud::http::Request& req) override;
	virtual std::unique_ptr<server_crud::http::Response> get_default_response(server_crud::http::Status status) override;
};

}