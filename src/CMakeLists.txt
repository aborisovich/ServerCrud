# SPDX-License-Identifier: Apache License 2.0
#
# Copyright(c) 2023 Andrey Borisovich. All rights reserved.
#
# Author: Andrey Borisovich <andrey@borisovich.com>
#

target_sources(ServerCrud PRIVATE
	"main.cpp"
	"ArgParser.cpp"
	"ServerCrud.cpp"
	"http/Connection.cpp"
	"http/RequestParser.cpp"
	"http/Response.cpp"
	"http/Status.cpp"
	"http/mime_types/JsonResponse.cpp"
	"http/mime_types/JsonRequestHandler.cpp")
