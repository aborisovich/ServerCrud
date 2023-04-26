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
	/**
	 * @brief Creates ArgParser instance.
	*/
	ArgParser();
	/**
	 * @brief Parse program input arguments.
	 * @param argc Arguments count.
	 * @param argv Artument array.
	 * @return Map of parsed arguments with assigned values.
	*/
	boost::program_options::variables_map parse_args(int argc, char* argv[]);

private:
	/**
	 * @brief Contains a list of supported program arguments.
	*/
	boost::program_options::options_description all_options = {"Allowed options"};

	/**
	 * @brief List of parsed options with corresponding values.
	*/
	boost::program_options::variables_map parsed_input;
};

}