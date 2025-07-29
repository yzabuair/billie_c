// Copyright 2025 Yasser Zabuair.  See LICENSE for details.
#pragma once

#include <core/ErrorHelpers.h>

#include <exception>
#include <sstream>
#include <string>

namespace billiec {

struct RuntimeError: public std::exception {
    ErrorCode ec;
    mutable std::string message;

    RuntimeError(ErrorCode ec):
        ec{std::move(ec)} {
    }
    
    const char* what() const noexcept override {
        if (message.empty()) {
            std::stringstream stream;
            stream << "RuntimeError: \n" << ec;
            message = stream.str();
        }

        return message.c_str();
    }
};
} // namespace billiec
