/* SPDX-License-Identifier: Apache License 2.0
 *
 * Copyright(c) 2023 Andrey Borisovich. All rights reserved.
 *
 * Author: Andrey Borisovich <andrey@borisovich.com>
 */

#include <ServerCrud/ArgParser.hpp>
#include <ServerCrud/TerminationHandler.hpp>
#include <ServerCrud/ServerCrud.hpp>
#include <ServerCrud/http/mime_types/JsonRequestHandler.hpp>
#ifdef WIN32
#include <ServerCrud/WindowsConsole.hpp>
#endif
#include <iostream>

int main(int argc, char* argv[])
{
#ifdef WIN32
	// Configures ServerCrud to be used from the Windows console
	SetConsoleCtrlHandler(server_crud::console_handler, TRUE);
#endif
	std::set_terminate(server_crud::on_terminate);
	if(std::atexit(server_crud::on_exit) != 0)
		throw std::runtime_error("Critical initialization error - failed to register exit handler\n");

	server_crud::ArgParser parser;
	boost::program_options::variables_map input_args;
	try
	{
		input_args = parser.parse_args(argc, argv);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << "\n";
		std::exit(-1);
	}

	server_crud::ServerCrud server = server_crud::ServerCrud(input_args["ip"].as<std::string>(),
		input_args["port"].as<int>(), 12, std::make_unique<server_crud::http::mime_types::JsonRequestHandler>());

	server.run();
	
	return 0;
}
