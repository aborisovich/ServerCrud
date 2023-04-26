 /* SPDX-License-Identifier: Apache License 2.0
  *
  * Copyright(c) 2023 Andrey Borisovich. All rights reserved.
  *
  * Author: Andrey Borisovich <andrey@borisovich.com>
  */
#include <ServerCrud/http/Status.hpp>

namespace server_crud::http
{

std::ostream& operator<<(std::ostream& stream, const Status& status)
{
    switch(status)
    {
        case Status::OK: return (stream << "Ok");
        case Status::CREATED: return (stream << "Created");
        case Status::ACCEPTED: return (stream << "Accepted");
        case Status::NO_CONTENT: return (stream << "No Content");
        case Status::MULTIPLE_CHOICES: return (stream << "Multiple Choices");
        case Status::MOVED_PERNAMENTLY: return (stream << "Moved Pernamently");
        case Status::MOVED_TEMPORARILY: return (stream << "Moved Temporarily");
        case Status::NOT_MODIFIED: return (stream << "Not Modified");
        case Status::BAD_REQUEST: return (stream << "Bad Request");
        case Status::UNAUTHORISED: return (stream << "Unauthorised");
        case Status::FORBIDDEN: return (stream << "Forbidden");
        case Status::NOT_FOUND: return (stream << "Not Found");
        case Status::INTERNAL_SERVER_ERROR: return (stream << "Internal Server Error");
        case Status::NOT_IMPLEMENTED: return (stream << "Not implemented");
        case Status::BAD_GATEWAY: return (stream << "Bad Gateway");
        case Status::SERVICE_UNAVAILABLE: return (stream << "Service Unavailable");
        default:
            throw std::runtime_error(std::format("Not implemented HTTP status code: {0}",
                static_cast<unsigned short>(status)));
    }
}

std::string to_string(const Status& status)
{
    std::stringstream os;
    os << status;
    return os.str();
}

}