// Copyright 2025 Yasser Zabuair.  See LICENSE for details.
#include <parser/LanguageParser.h>

#include <parser/Errors.h>
#include <parser/ParserError.h>

namespace billiec::parser {

LanguageParser::LanguageParser(std::vector<scanner::Token> tokens):
    tokens_{std::move(tokens)} {
}

ProgramNode::PtrType LanguageParser::parse_program() {
    return ProgramNode::create(parse_function_stmt_());
}

FunctionNode::PtrType LanguageParser::parse_function_stmt_() {
    consume_(scanner::TokenType::INT, "Expected int");
    auto func_name_token = consume_(scanner::TokenType::IDENTIFIER, "Expected name of function.");
    consume_(scanner::TokenType::LEFT_PAREN, "Expected left paren");
    consume_(scanner::TokenType::VOID, "Expected void");
    consume_(scanner::TokenType::RIGHT_PAREN, "Expected right paren");
    
    consume_(scanner::TokenType::LEFT_BRACE, "Expected left brace");
    
    return FunctionNode::create(func_name_token, parse_block_());
}

std::vector<AstNode::PtrType> LanguageParser::parse_block_() {
    std::vector<AstNode::PtrType> statements;
    
    while(!check_(scanner::TokenType::RIGHT_BRACE) && !is_at_end_()) {
        statements.push_back(parse_stmt_());
    }
    
    consume_(scanner::TokenType::RIGHT_BRACE, "Expected right brace");
    
    return statements;
}

AstNode::PtrType LanguageParser::parse_stmt_() {
    if (match_({scanner::TokenType::RETURN})) {
        return parse_return_stmt_();
    }
    
    // TODO: Error..
}

AstNode::PtrType LanguageParser::parse_return_stmt_() {
    scanner::Token keyword = previous_();
    
    auto return_expr = parse_expr_();
    
    consume_(scanner::TokenType::SEMICOLON, "Expected ';' after return value.");
    
    return ReturnNode::create(keyword, std::move(return_expr));
}

AstNode::PtrType LanguageParser::parse_expr_() {
    if (match_({scanner::TokenType::NUMBER})) {
        return parse_literal_expr_();
    } else if (match_({scanner::TokenType::MINUS, scanner::TokenType::COMPLEMENT})) {
        auto token = peek_();
        auto expr = parse_expr_();
        return parser::UnaryNode::create(token, std::move(expr));
    } else if (match_({scanner::TokenType::LEFT_PAREN})) {
        auto expr =  parse_expr_();
        consume_(scanner::TokenType::RIGHT_PAREN, "Expected ')'");
        return expr;
    } else {
        ErrorCode ec{make_error_code(errc::parser_invalid_expression), "Invalid expression."};
        throw ParserError{std::move(ec)};
    }
}

AstNode::PtrType LanguageParser::parse_literal_expr_() {
    return LiteralNode::create(previous_().token_value);
}

bool LanguageParser::check_(scanner::TokenType type) {
    if (is_at_end_()) {
        return false;
    }
    
    return peek_().token_type == type;
    
}

bool LanguageParser::match_(const std::vector<scanner::TokenType>& match_types) {
    for(auto curr_type: match_types) {
        // If we match any of the types in our match_types we found what we're looking for.
        if (check_(curr_type)) {
            advance_();
            return true;
        }
    }
    
    return false;
}

const scanner::Token& LanguageParser::consume_(scanner::TokenType token_type, const std::string& message) {
    if (check_(token_type)) {
        return advance_();
    }
    
    ErrorCode ec{make_error_code(errc::parser_unexpected_token), message};
    throw ParserError{std::move(ec)};
}


const scanner::Token& LanguageParser::peek_() {
    return tokens_[curr_token_idx_];
}

const scanner::Token& LanguageParser::advance_() {
    return tokens_[curr_token_idx_++];
}

const scanner::Token& LanguageParser::previous_() {
    return tokens_[curr_token_idx_-1];
}

bool LanguageParser::is_at_end_() {
    return peek_().token_type == scanner::TokenType::ENDOFFILE;
}

} // namespace billiec::parser
