/* SPDX-License-Identifier: Apache License 2.0
 *
 * Copyright(c) 2023 Andrey Borisovich. All rights reserved.
 *
 * Author: Andrey Borisovich <andrey@borisovich.com>
 */

#include <ServerCrud/ArgParser.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
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
