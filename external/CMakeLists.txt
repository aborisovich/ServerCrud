# SPDX-License-Identifier: Apache License 2.0
#
# Copyright(c) 2023 Andrey Borisovich. All rights reserved.
#
# Author: Andrey Borisovich <andrey@borisovich.com>
#

# Boost library
set(BOOST_INCLUDE_LIBRARIES asio json system program_options)
set(BOOST_ENABLE_CMAKE ON)
# Show git clone progress in console
set(FETCHCONTENT_QUIET FALSE)

set(BOOST_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/boost")
set(FETCHCONTENT_BASE_DIR "${BOOST_ROOT_DIR}")

include(FetchContent)
FetchContent_Declare(
  Boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.81.0
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE
  BINARY_DIR    "${BOOST_ROOT_DIR}/boost-build"
  SOURCE_DIR    "${BOOST_ROOT_DIR}/boost-src"
)
FetchContent_MakeAvailable(Boost)

target_link_libraries(ServerCrud PRIVATE
    Boost::asio
    Boost::json
    Boost::program_options
    Boost::system)
