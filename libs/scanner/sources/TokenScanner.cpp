// Copyright 2025, Yasser Zabuair.  See LICENSE for details.
#include <scanner/TokenScanner.h>

#include <scanner/Errors.h>
#include <scanner/ScannerError.h>

namespace billiec::scanner {

TokenScanner::TokenScanner(std::string inp_source):
    inp_source_{inp_source} {
    
}

std::vector<Token> TokenScanner::get_tokens() {
    while(!is_at_end_()) {
        start_ = current_;
        get_next_token_();
    }
    
    return std::move(tokens_);
}

void TokenScanner::get_next_token_() {
    char c = advance_();
    switch(c) {
        case '(':
            add_token_(TokenType::LEFT_PAREN);
            break;
            
        case ')':
            add_token_(TokenType::RIGHT_PAREN);
            break;
            
        case '{':
            add_token_(TokenType::LEFT_BRACE);
            break;
            
        case '}':
            add_token_(TokenType::RIGHT_BRACE);
            break;
            
        case ';':
            add_token_(TokenType::SEMICOLON);
            break;
            
        case '\n':
        case '\r':
            ++curr_line_;
            break;
            
        case '\t':
        case ' ':
            break;
            
        default:
            if (std::isdigit(c)) {
                number_();
            } else if (is_alpha_(c)) {
                identifier_();
            } else {
                auto ec = ErrorCode{make_error_code(errc::scanner_err_invalid_token), "Invalid token"};
                ec << "line: " << curr_line_ << ", at character:" << c;
                throw ScannerError{ec};
            }
            
            break;
    } // switch
}

bool TokenScanner::is_alpha_(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

bool TokenScanner::is_alpha_numeric_(char c) {
    if (is_alpha_(c) ||
        std::isdigit(c)) {
        return true;
    }
    return false;
}

void TokenScanner::number_() {
    while(std::isdigit(peek_())) {
        advance_();
    }
    
    std::string number_string = inp_source_.substr(start_, current_ - start_);
    
    add_token_(TokenType::NUMBER, std::stoi(number_string));
}

void TokenScanner::string_() {
    advance_();
    
    std::string str_value;
    while(peek_() != '\"' && !is_at_end_()) {
        str_value += peek_();
        advance_();
    }
    if (peek_() != '\"' && is_at_end_()) {
        // TODO: Error, unterminated string.
    }
    
    add_token_(TokenType::STRING, str_value);
}

void TokenScanner::identifier_() {
    while (is_alpha_numeric_(peek_())) {
        advance_();
    }
    
    std::string identifier = inp_source_.substr(start_, current_ - start_);
    auto itr = keywords_.find(identifier);
    if (itr == keywords_.end()) {
        add_token_(TokenType::IDENTIFIER, identifier);
    } else {
        add_token_(itr->second);
    }
}


void TokenScanner::add_token_(TokenType type) {
    auto lexeme = inp_source_.substr(start_, (current_ - start_));
    tokens_.push_back(Token{
        .token_type = type,
        .token_value = TokenValueType{},
        .lexeme = lexeme,
        .line = curr_line_
    });
}

void TokenScanner::add_token_(TokenType type, const TokenValueType& value) {
    auto lexeme = inp_source_.substr(start_, (current_ - start_));
    tokens_.push_back(Token{
        .token_type = type,
        .token_value = value,
        .lexeme = lexeme,
        .line = curr_line_
    });
}

char TokenScanner::advance_() {
    if (current_ >= inp_source_.size()) {
        // TODO: Error...
    }

    return inp_source_[current_++];
}

bool TokenScanner::is_at_end_() {
    return current_ >= inp_source_.size();
}

char TokenScanner::peek_() {
    if (is_at_end_()) {
        return '\0';
    }
   
    return inp_source_[current_];
}

char TokenScanner::peek_next_() {
    if (is_at_end_()) {
        return '\0';
    }
   
    if (current_ + 1 >= inp_source_.size()) {
        return '\0';
    }
   
    return inp_source_[current_ + 1];
}

} // namespace billiec::scanner

