/* SPDX-License-Identifier: Apache License 2.0
 *
 * Copyright(c) 2023 Andrey Borisovich. All rights reserved.
 *
 * Author: Andrey Borisovich <andrey@borisovich.com>
 */

#include <ServerCrud/ArgParser.hpp>
#include <ServerCrud/TerminationHandler.hpp>
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
	try
	{
		auto map = parser.parse_args(argc, argv);
		if(map)
			std::cout << "Starting server at TCP port: " <<
				map.value()["port"].as<int>() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << "\n";
	}
	
	return 0;
}
