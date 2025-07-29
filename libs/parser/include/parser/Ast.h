// Copyright 2025 Yasser Zabuair.  See LICENSE for details.
#pragma once

#include <scanner/Token.h>

#include <memory>
#include <vector>

namespace billiec::parser {

struct ProgramNode;
struct FunctionNode;
struct ReturnNode;
struct LiteralNode;

struct AstVisitor {
    AstVisitor(){ }
    virtual ~AstVisitor(){ }
    
    virtual void visit(const ProgramNode& node) = 0;
    virtual void visit(const FunctionNode& node) = 0;
    virtual void visit(const ReturnNode& node) = 0;
    virtual void visit(const LiteralNode& node) = 0;
};
    
struct AstNode {
    using PtrType = std::unique_ptr<AstNode>;
    
    AstNode(){ }
    virtual ~AstNode(){ }
    
    virtual void accept(AstVisitor& visitor) = 0;
};

// ---

struct ProgramNode: public AstNode {
    using PtrType = std::unique_ptr<ProgramNode>;
    std::unique_ptr<AstNode> function_definition;
    
    ProgramNode(std::unique_ptr<AstNode> function_definition):
        function_definition{std::move(function_definition)} {        
    }
    
    static PtrType create(std::unique_ptr<AstNode> function_definition) {
        return std::make_unique<ProgramNode>(std::move(function_definition));
    }
    
    void accept(AstVisitor& visitor) override {
        visitor.visit(*this);
    }
};

// ---

struct FunctionNode: public AstNode {
    using PtrType = std::unique_ptr<FunctionNode>;
    scanner::Token name;
    std::vector<std::unique_ptr<AstNode>> body;
    
    FunctionNode(const scanner::Token& name,
                 std::vector<std::unique_ptr<AstNode>> body):
        name{name},
        body{std::move(body)} {
        
    }
    
    static PtrType create(const scanner::Token name,
                   std::vector<std::unique_ptr<AstNode>> body) {
        return std::make_unique<FunctionNode>(name, std::move(body));
    }
    
    void accept(AstVisitor& visitor) override {
        visitor.visit(*this);
    }
};

// ---

struct ReturnNode: public AstNode {
    using PtrType = std::unique_ptr<ReturnNode>;
    scanner::Token token;
    std::unique_ptr<AstNode> return_expr;
    
    ReturnNode(const scanner::Token& token,
               std::unique_ptr<AstNode> return_expr):
        token{token},
        return_expr{std::move(return_expr)} {
        
    }
    
    static PtrType create(const scanner::Token& token,
                          std::unique_ptr<AstNode> return_expr) {
        return std::make_unique<ReturnNode>(token, std::move(return_expr));
    }
    
    void accept(AstVisitor& visitor) override {
        visitor.visit(*this);
    }
};

// ---

struct LiteralNode: public AstNode {
    using PtrType = std::unique_ptr<LiteralNode>;
    scanner::TokenValueType value;
    
    LiteralNode(const scanner::TokenValueType& value):
        value{value} {
        
    }
    
    static PtrType create(const scanner::TokenValueType& value) {
        return std::make_unique<LiteralNode>(value);
    }
    
    void accept(AstVisitor& visitor) override {
        visitor.visit(*this);
    }
};

} // namespace billiec::parser
