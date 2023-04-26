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

#include <ServerCrud/http/RequestParser.hpp>
#include <ServerCrud/http/Request.hpp>
#include <algorithm>

namespace server_crud::http
{

void RequestParser::reset()
{
	state = ParserState::METHOD_START;
}

std::optional<bool> RequestParser::consume(Request& req, char input)
{
    switch(state)
    {
        case ParserState::METHOD_START:
            if(!is_char(input) || is_ctl(input) || is_tspecial(input))
                return std::make_optional(false);
            else
            {
                state = ParserState::METHOD;
                req.method.push_back(input);
                return std::nullopt;
            }
        case ParserState::METHOD:
            if(input == ' ')
            {
                state = ParserState::URI;
                return std::nullopt;
            }
            else if(!is_char(input) || is_ctl(input) || is_tspecial(input))
                return std::make_optional(false);
            else
            {
                req.method.push_back(input);
                return std::nullopt;
            }
        case ParserState::URI_START:
            if(is_ctl(input))
                return std::make_optional(false);
            else
            {
                state = ParserState::URI;
                req.uri.push_back(input);
                return std::nullopt;
            }
        case ParserState::URI:
            if(input == ' ')
            {
                state = ParserState::HTTP_VERSION_H;
                return std::nullopt;
            }
            else if(is_ctl(input))
                return std::make_optional(false);
            else
            {
                req.uri.push_back(input);
                return std::nullopt;
            }
        case ParserState::HTTP_VERSION_H:
            if(input == 'H')
            {
                state = ParserState::HTTP_VERSION_T_1;
                return std::nullopt;
            }
            else
                return std::make_optional(false);
        case ParserState::HTTP_VERSION_T_1:
            if(input == 'T')
            {
                state = ParserState::HTTP_VERSION_T_2;
                return std::nullopt;
            }
            else
                return std::make_optional(false);
        case ParserState::HTTP_VERSION_T_2:
            if(input == 'T')
            {
                state = ParserState::HTTP_VERSION_P;
                return std::nullopt;
            }
            else
                return std::make_optional(false);
        case ParserState::HTTP_VERSION_P:
            if(input == 'P')
            {
                state = ParserState::HTTP_VERSION_SLASH;
                return std::nullopt;
            }
            else
                return std::make_optional(false);
        case ParserState::HTTP_VERSION_SLASH:
            if(input == '/')
            {
                req.http_version_major = 0;
                req.http_version_minor = 0;
                state = ParserState::HTTP_VERSION_MAJOR_START;
                return std::nullopt;
            }
            else
                return std::make_optional(false);
        case ParserState::HTTP_VERSION_MAJOR_START:
            if(is_digit(input))
            {
                req.http_version_major = req.http_version_major * 10 + input - '0';
                state = ParserState::HTTP_VERSION_MAJOR;
                return std::nullopt;
            }
            else
                return std::make_optional(false);
        case ParserState::HTTP_VERSION_MAJOR:
            if(input == '.')
            {
                state = ParserState::HTTP_VERSION_MINOR_START;
                return std::nullopt;
            }
            else if(is_digit(input))
            {
                req.http_version_major = req.http_version_major * 10 + input - '0';
                return std::nullopt;
            }
            else
                return std::make_optional(false);
        case ParserState::HTTP_VERSION_MINOR_START:
            if(is_digit(input))
            {
                req.http_version_minor = req.http_version_minor * 10 + input - '0';
                state = ParserState::HTTP_VERSION_MINOR;
                return std::nullopt;
            }
            else
                return std::make_optional(false);
        case ParserState::HTTP_VERSION_MINOR:
            if(input == '\r')
            {
                state = ParserState::EXPECTING_NEWLINE_1;
                return std::nullopt;
            }
            else if(is_digit(input))
            {
                req.http_version_minor = req.http_version_minor * 10 + input - '0';
                return std::nullopt;
            }
            else
                return std::make_optional(false);
        case ParserState::EXPECTING_NEWLINE_1:
            if(input == '\n')
            {
                state = ParserState::HEADER_LINE_START;
                return std::nullopt;
            }
            else
                return std::make_optional(false);
        case ParserState::HEADER_LINE_START:
            if(input == '\r')
            {
                state = ParserState::EXPECTING_NEWLINE_3;
                return std::nullopt;
            }
            else if(!req.headers.empty() && (input == ' ' || input == '\t'))
            {
                state = ParserState::HEADER_LWS;
                return std::nullopt;
            }
            else if(!is_char(input) || is_ctl(input) || is_tspecial(input))
                return std::make_optional(false);
            else
            {
                req.headers.push_back(Header());
                req.headers.back().name.push_back(input);
                state = ParserState::HEADER_NAME;
                return std::nullopt;
            }
        case ParserState::HEADER_LWS:
            if(input == '\r')
            {
                state = ParserState::EXPECTING_NEWLINE_2;
                return std::nullopt;
            }
            else if(input == ' ' || input == '\t')
                return std::nullopt;
            else if(is_ctl(input))
                return std::make_optional(false);
            else
            {
                state = ParserState::HEADER_VALUE;
                req.headers.back().value.push_back(input);
                return std::nullopt;
            }
        case ParserState::HEADER_NAME:
            if(input == ':')
            {
                state = ParserState::SPACE_BEFORE_HEADER_VALUE;
                return std::nullopt;
            }
            else if(!is_char(input) || is_ctl(input) || is_tspecial(input))
                return std::make_optional(false);
            else
            {
                req.headers.back().name.push_back(input);
                return std::nullopt;
            }
        case ParserState::SPACE_BEFORE_HEADER_VALUE:
            if(input == ' ')
            {
                state = ParserState::HEADER_VALUE;
                return std::nullopt;
            }
            else
                return std::make_optional(false);
        case ParserState::HEADER_VALUE:
            if(input == '\r')
            {
                state = ParserState::EXPECTING_NEWLINE_2;
                return std::nullopt;
            }
            else if(is_ctl(input))
                return std::make_optional(false);
            else
            {
                req.headers.back().value.push_back(input);
                return std::nullopt;
            }
        case ParserState::EXPECTING_NEWLINE_2:
            if(input == '\n')
            {
                state = ParserState::HEADER_LINE_START;
                return std::nullopt;
            }
            else
                return std::make_optional(false);
        case ParserState::EXPECTING_NEWLINE_3:
            return (input == '\n');
        default:
            return std::make_optional(false);
    }
}

bool RequestParser::is_char(int c)
{
	return c >= 0 && c <= 127;
}

bool RequestParser::is_ctl(int c)
{
	return c >= 0 && c <= 31 || c == 127;
}

bool RequestParser::is_tspecial(int c)
{
	return (std::find(special_characters.begin(), special_characters.end(), static_cast<const char>(c))
		!= special_characters.end());
}

bool RequestParser::is_digit(int c)
{
	return c >= '0' && c <= '9';
}

}