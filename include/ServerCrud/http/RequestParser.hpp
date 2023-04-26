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
#include <tuple>
#include <optional>
#include <list>
#include <iterator>

namespace server_crud::http
{

class RequestParser
{
public:
    /// Parse some data. The tribool return value is true when a complete request
    /// has been parsed, false if the data is invalid, indeterminate when more
    /// data is required. The InputIterator return value indicates how much of the
    /// input has been consumed.
    template <typename InputIterator>
    std::tuple<std::optional<bool>, InputIterator> parse(Request& req, InputIterator begin, InputIterator end)
        requires std::input_iterator<InputIterator>
    {
        while(begin != end)
        {
            std::optional<bool> result = consume(req, *begin++);
            if(result.has_value())
                return std::make_tuple(result, begin);
        }
        return std::make_tuple(std::nullopt, begin);
    }

	/**
		* @brief Resets RequestParser to the initial state.
	*/
    void reset();

private:
    /**
     * @brief Possible states of the parser.
    */
    enum class ParserState
    {
        METHOD_START,
        METHOD,
        URI_START,
        URI,
        HTTP_VERSION_H,
        HTTP_VERSION_T_1,
        HTTP_VERSION_T_2,
        HTTP_VERSION_T_3,
        HTTP_VERSION_P,
        HTTP_VERSION_SLASH,
        HTTP_VERSION_MAJOR_START,
        HTTP_VERSION_MAJOR,
        HTTP_VERSION_MINOR_START,
        HTTP_VERSION_MINOR,
        EXPECTING_NEWLINE_1,
        HEADER_LINE_START,
        HEADER_LWS,
        HEADER_NAME,
        SPACE_BEFORE_HEADER_VALUE,
        HEADER_VALUE,
        EXPECTING_NEWLINE_2,
        EXPECTING_NEWLINE_3
    };

    /// Handle the next character of input.
    std::optional<bool> consume(Request& req, char input);

    /// Check if a byte is an HTTP character.
    bool is_char(int c);

    /// Check if a byte is an HTTP control character.
    bool is_ctl(int c);

    /// Check if a byte is defined as an HTTP tspecial character.
    bool is_tspecial(int c);

    /// Check if a byte is a digit.
    bool is_digit(int c);

    /**
     * @brief Represents current state of the parser.
    */
    ParserState state{ParserState::METHOD_START};

    const std::list<char> special_characters {
        '(', ')', '<', '>', '@', ',', ';', ':', '\\', '"', '/', '[', ']', '?', '=',
        '{', '}', ' ', '\t'
    };
};

}
