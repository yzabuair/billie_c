// Copyright 2025 Yasser Zabuair.  See LICENSE for details.
#pragma once

#include <codegen/AssemblerAst.h>
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

struct TackyNodeVisitor {
    TackyNodeVisitor() = default;
    virtual ~TackyNodeVisitor() = default;
    
    virtual std::unique_ptr<AssemblerNode> visit(const ProgramTackyNode& node) = 0;
    virtual std::unique_ptr<AssemblerNode> visit(const FunctionTackyNode& node) = 0;
    virtual std::unique_ptr<AssemblerNode> visit(const ReturnTackyNode& node) = 0;
    virtual std::unique_ptr<AssemblerNode> visit(const UnaryTackyNode& node) = 0;
    virtual std::unique_ptr<AssemblerNode> visit(const IntConstTackyNode& node) = 0;
    virtual std::unique_ptr<AssemblerNode> visit(const VarTackyNode& node) = 0;
};


struct TackyNode {
    using PtrType = std::unique_ptr<TackyNode>;
    
    TackyNode() = default;
    virtual ~TackyNode() = default;
    
    virtual std::unique_ptr<AssemblerNode> accept(TackyNodeVisitor& visitor) = 0;
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
    
    std::unique_ptr<AssemblerNode> accept(TackyNodeVisitor& visitor) override {
        return visitor.visit(*this);
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
    
    std::unique_ptr<AssemblerNode> accept(TackyNodeVisitor& visitor) override {
        return visitor.visit(*this);
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
    
    std::unique_ptr<AssemblerNode> accept(TackyNodeVisitor& visitor) override {
        return visitor.visit(*this);
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
    
    std::unique_ptr<AssemblerNode> accept(TackyNodeVisitor& visitor) override {
        return visitor.visit(*this);
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
    
    std::unique_ptr<AssemblerNode> accept(TackyNodeVisitor& visitor) override {
        return visitor.visit(*this);
    }
};

// ---

struct VarTackyNode: public TackyNode {
    using PtrType = std::unique_ptr<VarTackyNode>;
    std::string var_name;
    
    VarTackyNode(const std::string& var_name): var_name{var_name} {
    }
    
    static PtrType create(const std::string& var_name) {
        return std::make_unique<VarTackyNode>(var_name);
    }
    
    std::unique_ptr<AssemblerNode> accept(TackyNodeVisitor& visitor) override {
        return visitor.visit(*this);
    }
};

// ---


} // namespace billiec::codegen
