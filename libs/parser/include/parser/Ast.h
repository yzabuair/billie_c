// Copyright 2025 Yasser Zabuair.  See LICENSE for details.
#pragma once

#include <scanner/Token.h>

#include <any>
#include <functional>
#include <memory>
#include <variant>
#include <vector>

namespace billiec::parser {

struct ProgramNode;
struct FunctionNode;
struct ReturnNode;
struct UnaryNode;
struct LiteralNode;


template <typename R>
struct AstNodeVisitor {
    using ReturnType = R;
    
    AstNodeVisitor() = default;
    virtual ~AstNodeVisitor() = default;
    
    virtual R visit(const ProgramNode& node) = 0;
    virtual R visit(const FunctionNode& node) = 0;
    virtual R visit(const ReturnNode& node) = 0;
    virtual R visit(const UnaryNode& node) = 0;
    virtual R visit(const LiteralNode& node) = 0;
};

struct AstNode {
    using PtrType = std::unique_ptr<AstNode>;
    
    AstNode() = default;
    virtual ~AstNode() = default;
};

// ---

struct LiteralNode: public AstNode  {
    using PtrType = std::unique_ptr<LiteralNode>;
    
    scanner::TokenValueType value;

    LiteralNode(const scanner::TokenValueType& value):
        value{value} {
    }
    
    static PtrType create(const scanner::TokenValueType& value) {
        return std::make_unique<LiteralNode>(value);
    }
};

// ---

struct UnaryNode: public AstNode {
    using PtrType = std::unique_ptr<UnaryNode>;
    
    scanner::Token operation;
    AstNode::PtrType expr;

    UnaryNode(const scanner::Token& operation,
              AstNode::PtrType expr):
        operation{operation},
        expr{std::move(expr)} {
    }
    
    static PtrType create(const scanner::Token& operation,
                          AstNode::PtrType expr) {
        return std::make_unique<UnaryNode>(operation, std::move(expr));
    }
};

// ---

struct ReturnNode: public AstNode {
    using PtrType = std::unique_ptr<ReturnNode>;
    
    scanner::Token token;
    AstNode::PtrType return_expr;

    ReturnNode(const scanner::Token& token,
               AstNode::PtrType return_expr):
        token{token},
        return_expr{std::move(return_expr)} {
    }
    
    static PtrType create(const scanner::Token& token,
                          AstNode::PtrType return_expr) {
        return std::make_unique<ReturnNode>(token, std::move(return_expr));
    }

};

// ---

struct FunctionNode: public AstNode {
    using PtrType = std::unique_ptr<FunctionNode>;
    scanner::Token name;
    std::vector<AstNode::PtrType> body;
    
    FunctionNode(const scanner::Token& name,
                 std::vector<AstNode::PtrType> body):
        name{name},
        body{std::move(body)} {
    }
    
    static PtrType create(const scanner::Token& name,
                          std::vector<AstNode::PtrType> body) {
        return std::make_unique<FunctionNode>(name, std::move(body));
    }
};

// ---

struct ProgramNode: public AstNode {
    using PtrType = std::unique_ptr<ProgramNode>;
    AstNode::PtrType function_node;
    
    ProgramNode(AstNode::PtrType function_node):
        function_node{std::move(function_node)} {
    }
    
    static PtrType create(AstNode::PtrType function_node) {
        return std::make_unique<ProgramNode>(std::move(function_node));
    }
    
};

// ---

template <typename T, typename U>
typename T::ReturnType accept(T& visitor, const U& node) {
    return visitor.visit(node);
}

template <typename T>
typename T::ReturnType accept(T& visitor, const AstNode::PtrType& node) {
    if (auto actual_node = dynamic_cast<const ProgramNode*>(node.get())) {
        return visitor.visit(*actual_node);
    } else if (auto actual_node = dynamic_cast<const FunctionNode*>(node.get())) {
        return visitor.visit(*actual_node);
    } else if (auto actual_node = dynamic_cast<const ReturnNode*>(node.get())) {
        return visitor.visit(*actual_node);
    } else if (auto actual_node = dynamic_cast<const UnaryNode*>(node.get())) {
        return visitor.visit(*actual_node);
    } else if (auto actual_node = dynamic_cast<const LiteralNode*>(node.get())) {
        return visitor.visit(*actual_node);
    } else {
        // TODO: Error...
        std::cout << "Hey, what happen\n";
    }
}

} // namespace billiec::parser
