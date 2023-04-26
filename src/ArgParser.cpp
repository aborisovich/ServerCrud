/* SPDX-License-Identifier: Apache License 2.0
 *
 * Copyright(c) 2023 Andrey Borisovich. All rights reserved.
 *
 * Author: Andrey Borisovich <andrey@borisovich.com>
 */

#include <ServerCrud/ArgParser.hpp>
#include <ServerCrud/config.hpp>
#include <boost/asio/ip/address.hpp>
#include <iostream>
#include <limits>
#include <format>

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
        ("ip,i", boost::program_options::value<std::string>()->default_value("::1"),
        "IPv6 or IPv4 address")
        ("port,p", boost::program_options::value<int>()->default_value(8080),
            "select TCP port number")
        ("threads,t", boost::program_options::value<int>()->default_value(4),
            "number of threads to be used by the server");

    all_options.add(info_options).add(server_config);
}

boost::program_options::variables_map ArgParser::parse_args(int argc, char* argv[])
{
	boost::program_options::store(boost::program_options::parse_command_line(argc, argv, all_options),
        parsed_input);
    boost::program_options::notify(parsed_input);
    if(parsed_input.count("help"))
    {
        std::cout << all_options << std::endl;
        std::exit(0);
    }

    if(parsed_input.count("version"))
    {
        std::cout << PROJECT_VER << std::endl;
        std::exit(0);
    }

    boost::system::error_code ip_address_parse_ec;
    /* @note BOOST ASIO IP address string may contain port number, but IP API is retarded and
    * does not allow to retrieve this port value. As work-around @see ServerCrud ignores port provided in the
    IP address argument. */
    boost::asio::ip::address address = boost::asio::ip::make_address(parsed_input["ip"].as<std::string>(), ip_address_parse_ec);

    if(ip_address_parse_ec.failed() || address.is_unspecified())
        throw boost::program_options::validation_error(
            boost::program_options::validation_error::invalid_option_value,
            "ip"
        );

    // Check if provided port number is valid - is in rage of {1, 65535}
    int port_nr = parsed_input["port"].as<int>();
    if(port_nr > USHRT_MAX || port_nr < 1)
        throw boost::program_options::validation_error(
            boost::program_options::validation_error::invalid_option_value,
            "port",
            std::to_string(port_nr)
        );

    int thread_count = parsed_input["threads"].as<int>();
    if(thread_count < 1)
        throw boost::program_options::validation_error(
            boost::program_options::validation_error::invalid_option_value,
            "threads",
            "Number of threads must be positive value");

    // Windows OS allows maximum of 64 threads per-process.
    // If this number is exceeded, threads are put into groups and context switching
    // becomes slower.
    if(thread_count > 64)
        throw boost::program_options::validation_error(
            boost::program_options::validation_error::invalid_option_value,
            "threads",
            "Number of threads must not exceed 64");

    return boost::program_options::variables_map{parsed_input};
}

}
