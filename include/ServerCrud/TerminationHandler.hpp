/* SPDX-License-Identifier: Apache License 2.0
 *
 * Copyright(c) 2023 Andrey Borisovich. All rights reserved.
 *
 * Author: Andrey Borisovich <andrey@borisovich.com>
 */

#pragma once
#include <exception>
#include <iostream>
#ifdef WIN32
#include <windows.h>
#endif

namespace server_crud
{

/**
 * @brief Exit handler executed when system performs a normal termination with
 * proper resources release.
*/
void on_exit()
{
    std::cout << "Terminating ServerCrud instance.\n";
}

/**
 * @brief Termination handler that is called when std::terminate is called
 * by the system.
*/
[[noreturn]] void on_terminate() noexcept
{
    unsigned int return_value = 0;
    // Handle existing exception from stack unwinding
    if(auto exc = std::current_exception())
    {
        // we have an exception
        try
        {
            std::rethrow_exception(exc); // throw to recognize the type
        }
        catch(const std::exception& exc)
        {
            std::cerr << "Fatal exception occurred: " << exc.what() << std::endl;
            return_value = 1;
        }
        catch(...)
        {
            std::cerr << "Critical unhandled exception occurred, terminating\n";
            return_value = 0xffffffff;
        }
    }

#ifdef WIN32
    ExitProcess(return_value);
#endif
}

}