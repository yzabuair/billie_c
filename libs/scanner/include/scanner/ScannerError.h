// Copyright 2025 Yasser Zabuair.  See LICENSE for details.
#pragma once

#include <core/ErrorHelpers.h>

#include <exception>
#include <sstream>
#include <string>

namespace billiec::scanner {

struct ScannerError: public std::exception {
    ErrorCode ec;
    mutable std::string message;

    ScannerError(ErrorCode ec):
        ec{std::move(ec)} {
    }
    
    const char* what() const noexcept override {
        if (message.empty()) {
            std::stringstream stream;
            stream << "ScannerError: \n" << ec;
            message = stream.str();
        }

        return message.c_str();
    }
};

} // namespace billiec::scanner
