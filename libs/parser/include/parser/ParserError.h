// Copyright 2025 Yasser Zabuair.  See LICENSE for detials.
#pragma once

#include <core/ErrorHelpers.h>

#include <exception>
#include <sstream>
#include <string>

namespace billiec::parser {

struct ParserError: public std::exception {
    ErrorCode ec;
    mutable std::string  message; 

    ParserError(ErrorCode ec):
        ec{std::move(ec)} {
    }

    const char* what() const noexcept override {
        if (message.empty()) {
            std::stringstream stream;
            stream << "ParserError: \n" << ec;
            message = stream.str();
        }

        return message.c_str();
    }
};

} // namespace billiec::parser
