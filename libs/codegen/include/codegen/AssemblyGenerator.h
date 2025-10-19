// Copyright 2025 Yasser Zabuair.  See LICENSE for details.
#pragma once

#include <codegen/AssemblerAst.h>
#include <codegen/TackyAst.h>
#include <parser/Ast.h>

#include <any>
#include <map>
#include <vector>

namespace billiec::codegen {

struct AssemblyGenerator: public TackyNodeVisitor {
    TackyNode::PtrType program_node;
    std::vector<AssemblerNode::PtrType> instructions;
    
    AssemblyGenerator(TackyNode::PtrType program_node): program_node{std::move(program_node)} {
    }
    
    std::vector<std::unique_ptr<AssemblerNode>> generate_assembly();
    std::unique_ptr<AssemblerNode> visit(const ProgramTackyNode& node) override;
    std::unique_ptr<AssemblerNode> visit(const FunctionTackyNode& node) override;
    std::unique_ptr<AssemblerNode> visit(const ReturnTackyNode& node) override;
    std::unique_ptr<AssemblerNode> visit(const UnaryTackyNode& node) override;
    std::unique_ptr<AssemblerNode> visit(const IntConstTackyNode& node) override;
    std::unique_ptr<AssemblerNode> visit(const VarTackyNode& node) override;
};



};
