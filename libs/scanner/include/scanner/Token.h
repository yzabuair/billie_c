// Copyright 2025, Yasser Zabuair.  See LICENSE for details.
#pragma once

#include <scanner/TokenType.h>

#include <string>
#include <variant>

namespace billiec::scanner {

using TokenValueType = std::variant<std::monostate, std::string, int, bool, nullptr_t>;

/** @brief  Represents the tokens from the input stream. */
struct Token {
    TokenType       token_type;
    TokenValueType  token_value;
    std::string     lexeme;
    int             line{0};
};

inline std::ostream& operator<<(std::ostream& ostream, const TokenValueType& value) {
    switch (value.index()) {
        case 0:
            ostream << "empty";
            break;
        case 1:
            ostream << "string: " << std::get<std::string>(value);
            break;
        case 2:
            ostream << "int: " << std::get<int>(value);
            break;
        case 3:
            ostream << "bool: " << std::get<bool>(value);
            break;
        case 4:
            ostream << "nullptr";
            break;
        default:
            ostream << "unknown";
            break;
    }
    return ostream;
}

inline std::ostream& operator<<(std::ostream& ostream, const Token& token) {
    ostream << "token_type: " << token.token_type << "\n";
    ostream << "token_value: " << token.token_value << "\n";
    ostream << "lexeme: " << token.lexeme << "\n";
    ostream << "line: " << token.line << "\n";
    return ostream;
}

} // namespace billiec::scanner
