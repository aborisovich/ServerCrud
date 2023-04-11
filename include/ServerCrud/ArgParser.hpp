/* SPDX-License-Identifier: Apache License 2.0
 *
 * Copyright(c) 2023 Andrey Borisovich. All rights reserved.
 *
 * Author: Andrey Borisovich <andrey@borisovich.com>
 */

#pragma once
#include <boost/program_options.hpp>
#include <optional>

namespace server_crud
{

/**
 * @brief Defines allowed program input arguments and parses provided by user input.
*/
class ArgParser final
{
public:
	ArgParser();
	std::optional<boost::program_options::variables_map> parse_args(int argc, char* argv[]);

private:
	/**
	 * @brief Contains a list of supported program arguments.
	*/
	boost::program_options::options_description all_options = {"Allowed options"};
	boost::program_options::variables_map parsed_input;
};

}