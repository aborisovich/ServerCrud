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

#include <string>

namespace server_crud::http
{

/**
 * @brief Represents HTTP header.
*/
struct Header
{
	/**
	 * @brief Header name element.
	*/
	std::string name;

	/**
	 * @brief Header value element.
	*/
	std::string value;

	/**
	 * @brief Set of characters used to separate HTTP header name element
	 * from value.
	*/
	static inline const char name_value_separator[] = {':', ' '};

	/**
	 * @brief Set of characters representing End Of Line (EOL) in internet protocol.
	*/
	static inline const char crlf[] = {'\r', '\n'};
};

}
