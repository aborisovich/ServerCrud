# SPDX-License-Identifier: Apache License 2.0
#
# Copyright(c) 2023 Andrey Borisovich. All rights reserved.
#
# Author: Andrey Borisovich <andrey@borisovich.com>
#
cmake_minimum_required (VERSION 3.23)

project(ServerCrud VERSION 1.0.0
	DESCRIPTION "Simple Rest server implementation"
	LANGUAGES CXX C)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT
	"$<$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>:$<$<CONFIG:Debug>:ProgramDatabase>>")
endif()

add_executable(ServerCrud)
set_property(TARGET ServerCrud PROPERTY CXX_STANDARD 20)

# Define supported Windows version - Windows 10
# https://learn.microsoft.com/en-us/cpp/porting/modifying-winver-and-win32-winnt?redirectedfrom=MSDN&view=msvc-170
target_compile_definitions(ServerCrud PRIVATE _WIN32_WINNT=0x0A00)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(external)
