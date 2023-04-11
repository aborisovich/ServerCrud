/* SPDX-License-Identifier: Apache License 2.0
 *
 * Copyright(c) 2023 Andrey Borisovich. All rights reserved.
 *
 * Author: Andrey Borisovich <andrey@borisovich.com>
 */

#include <ServerCrud/ArgParser.hpp>
#include <iostream>
#include <limits>

namespace server_crud
{

ArgParser::ArgParser()
{
    // Declare a group of options that will be 
    // allowed only on command line
    boost::program_options::options_description info_options("Generic options");
    info_options.add_options()
        ("version,v", "show version")
        ("help,h", "display help message");

    // Declare a group of options that will be 
    // allowed both on command line and in
    // config file
    boost::program_options::options_description server_config("Server configuration");
    server_config.add_options()
        ("port,p", boost::program_options::value<int>()->default_value(8080),
            "select TCP port number");

    all_options.add(info_options).add(server_config);
}

std::optional<boost::program_options::variables_map> ArgParser::parse_args(int argc, char* argv[])
{
	boost::program_options::store(boost::program_options::parse_command_line(argc, argv, all_options),
        parsed_input);
    boost::program_options::notify(parsed_input);
    if(parsed_input.count("help"))
    {
        std::cout << all_options << std::endl;
        return std::nullopt;
    }

    // Check if provided port number is valid - is in rage of {1, 65535}
    int port_nr = parsed_input["port"].as<int>();
    if(port_nr > USHRT_MAX || port_nr < 1)
        throw boost::program_options::validation_error(
            boost::program_options::validation_error::invalid_option_value,
            "port",
            std::to_string(port_nr)
        );
    return std::optional<boost::program_options::variables_map>{parsed_input};
}

}
