// Copyright 2025 Yasser Zabuair.  See LICENSE for details.
#pragma once

#include <scanner/Token.h>

#include <iostream>
#include <memory>
#include <vector>

namespace billiec::codegen {

// Forwards
struct ProgramTackyNode;
struct FunctionTackyNode;
struct ReturnTackyNode;
struct UnaryTackyNode;
struct IntConstTackyNode;
struct VarTackyNode;

// ---

struct TackyNode {
    using PtrType = std::unique_ptr<TackyNode>;
    
    TackyNode() = default;
    virtual ~TackyNode() = default;
    
    virtual std::ostream& generate(std::ostream& ostream) = 0;
};

// ---

struct ProgramTackyNode: public TackyNode {
    using PtrType = std::unique_ptr<ProgramTackyNode>;
    std::unique_ptr<TackyNode> function_definition;
    
    ProgramTackyNode(std::unique_ptr<TackyNode> function_definition):
        function_definition{std::move(function_definition)} {
    }
    
    static PtrType create(std::unique_ptr<TackyNode> function_definition) {
        return std::make_unique<ProgramTackyNode>(std::move(function_definition));
    }
    
    std::ostream& generate(std::ostream& ostream) override {
        return ostream;
    }
};

// ---

struct FunctionTackyNode: public TackyNode {
    using PtrType = std::unique_ptr<FunctionTackyNode>;
    scanner::Token name;
    std::vector<TackyNode::PtrType> instructions;
    
    FunctionTackyNode(const scanner::Token& name,
                      std::vector<TackyNode::PtrType> instructions):
        name{name},
        instructions{std::move(instructions)} {
    }
    
    static PtrType create(const scanner::Token& name,
                          std::vector<TackyNode::PtrType> instructions) {
        return std::make_unique<FunctionTackyNode>(name, std::move(instructions));
    }
    
    std::ostream& generate(std::ostream& ostream) override {
        return ostream;
    }
};

// ---

struct ReturnTackyNode: public TackyNode {
    using PtrType = std::unique_ptr<ReturnTackyNode>;
    TackyNode::PtrType return_expr;
    
    ReturnTackyNode(TackyNode::PtrType return_expr):
        return_expr{std::move(return_expr)} {
    }
    
    static PtrType create(TackyNode::PtrType return_expr) {
        return std::make_unique<ReturnTackyNode>(std::move(return_expr));
    }
    
    std::ostream& generate(std::ostream& ostream) override {
        return ostream;
    }
};

// ---

struct UnaryTackyNode: public TackyNode {
    using PtrType = std::unique_ptr<UnaryTackyNode>;
    scanner::Token operation;
    std::unique_ptr<TackyNode> src;
    std::unique_ptr<TackyNode> dst;
    
    UnaryTackyNode(const scanner::Token& operation,
                   std::unique_ptr<TackyNode> src,
                   std::unique_ptr<TackyNode> dst):
        operation{operation},
        src{std::move(src)},
        dst{std::move(dst)} {
    }
    
    static PtrType create(const scanner::Token& operation,
                          std::unique_ptr<TackyNode> src,
                          std::unique_ptr<TackyNode> dst) {
        return std::make_unique<UnaryTackyNode>(operation, std::move(src), std::move(dst));
    }
    
    std::ostream& generate(std::ostream& ostream) override {
        return ostream;
    }
};

// ---

struct IntConstTackyNode: public TackyNode {
    using PtrType = std::unique_ptr<IntConstTackyNode>;
    int value;
    
    IntConstTackyNode(int value): value{value} {
    }
    
    static PtrType create(int value) {
        return std::make_unique<IntConstTackyNode>(value);
    }
    
    std::ostream& generate(std::ostream& ostream) override {
        return ostream;
    }
};

// ---

struct VarTackyNode: public TackyNode {
    using PtryType = std::unique_ptr<VarTackyNode>;
    scanner::Token var_token;
    
    VarTackyNode(const scanner::Token& var_token): var_token{var_token} {
    }
    
    static PtrType create(const scanner::Token& var_token) {
        return std::make_unique<VarTackyNode>(var_token);
    }
    
    std::ostream& generate(std::ostream& ostream) override {
        return ostream;
    }
};







} // namespace billiec::codegen
