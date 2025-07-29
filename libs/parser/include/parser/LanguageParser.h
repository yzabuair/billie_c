// Copyright 2025 Yasser Zabuair.  See LICENSE for details.
#pragma once

#include <core/ErrorHelpers.h>
#include <parser/Ast.h>
#include <scanner/Token.h>

#include <expected>
#include <string>
#include <vector>

namespace billiec::parser {

class LanguageParser {
private:
    std::vector<scanner::Token> tokens_;
    int curr_token_idx_{0};
    
public:
    LanguageParser(std::vector<scanner::Token> tokens);
    
    AstNode::PtrType parse_program();
    
private:
    AstNode::PtrType parse_function_stmt_();
    std::vector<AstNode::PtrType> parse_block_();
    AstNode::PtrType parse_stmt_();
    AstNode::PtrType parse_return_stmt_();
    AstNode::PtrType parse_expr_();
    AstNode::PtrType parse_literal_expr_();
    bool check_(scanner::TokenType type);
    bool match_(const std::vector<scanner::TokenType>& token_types);
    const scanner::Token& consume_(scanner::TokenType token_type, const std::string& message);
    const scanner::Token& peek_();
    const scanner::Token& advance_();
    const scanner::Token& previous_();
    bool is_at_end_();
    
};

} // namespace billiec::parser

