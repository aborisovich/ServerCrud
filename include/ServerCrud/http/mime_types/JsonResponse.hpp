/* SPDX-License-Identifier: Apache License 2.0
 *
 * Copyright(c) 2023 Andrey Borisovich. All rights reserved.
 *
 * Author: Andrey Borisovich <andrey@borisovich.com>
 */

#pragma once
#include <ServerCrud/http/Response.hpp>
#include <ServerCrud/http/Status.hpp>
#include <boost/json.hpp>
#include <memory>

namespace server_crud::http::mime_types
{
/**
	* @brief This class represents HTTP response of content-type: application/json
	* charset: utf-8 described in the IANA standard https://www.rfc-editor.org/rfc/rfc8259.html .
*/
class JsonResponse final : public server_crud::http::Response
{
public:
	virtual std::unique_ptr<server_crud::http::Response> get_stock(server_crud::http::Status status) const override;
};

}
