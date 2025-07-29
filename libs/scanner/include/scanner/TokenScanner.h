// Copyright 2025, Yasser Zabuair.  See LICENSE for details.
#pragma once
#include <core/ErrorHelpers.h>
#include <scanner/Token.h>

#include <expected>
#include <map>
#include <vector>

namespace billiec::scanner {


/** @brief  This class is used to scan tokens and return a stream of tokens that are used by the parser. */
class TokenScanner {
private:
    std::string         inp_source_;
    std::vector<Token>  tokens_;
    int                 start_{0};
    int                 current_{0};
    int                 curr_line_{1};
    const std::map<std::string, TokenType> keywords_ = {
        {"and", TokenType::AND},
        {"else", TokenType::ELSE},
        {"false", TokenType::FALSE},
        {"for", TokenType::FOR},
        {"fun", TokenType::FUN},
        {"if", TokenType::IF},
        {"or", TokenType::OR},
        {"print", TokenType::PRINT},
        {"return", TokenType::RETURN},
        {"true", TokenType::TRUE},
        {"while", TokenType::WHILE},
        {"int", TokenType::INT},
        {"void", TokenType::VOID}
    };
    
public:
    TokenScanner(std::string inp_source);
    std::vector<Token> get_tokens();
    
private:
    void get_next_token_();
    bool is_alpha_(char c);
    bool is_alpha_numeric_(char c);
    void number_();
    void string_();
    void identifier_();
    void add_token_(TokenType type);
    void add_token_(TokenType type, const TokenValueType& value);
    char advance_();
    bool is_at_end_();
    char peek_();
    char peek_next_();
    
};



} // namespace billiec::scanner
