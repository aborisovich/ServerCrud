# SPDX-License-Identifier: Apache License 2.0
#
# Copyright(c) 2023 Andrey Borisovich. All rights reserved.
#
# Author: Andrey Borisovich <andrey@borisovich.com>
#

# Add source to this project's executable.
target_include_directories(ServerCrud PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

configure_file("${PROJECT_SOURCE_DIR}/cmake/config.hpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/ServerCrud/config.hpp")
