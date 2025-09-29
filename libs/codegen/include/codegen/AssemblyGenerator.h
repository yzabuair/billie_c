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
    
    std::vector<std::unique_ptr<AssemblerNode>> generate_assembly() {
        instructions.clear();
        
        auto curr_node = program_node->accept(*this);
        instructions.push_back(std::move(curr_node));
        
        return std::move(instructions);
    }
    
    std::unique_ptr<AssemblerNode> visit(const ProgramTackyNode& node) override {
        return ProgramAssemblerNode::create(node.function_definition->accept(*this));
    }
    
    std::unique_ptr<AssemblerNode> visit(const FunctionTackyNode& node) override {
        std::vector<std::unique_ptr<AssemblerNode>> instructions;
        
        for(const auto& curr_node: node.instructions) {
            instructions.push_back(curr_node->accept(*this));
        }
        
        return FunctionAssemblerNode::create(node.name, std::move(instructions));
    }
    
    std::unique_ptr<AssemblerNode> visit(const ReturnTackyNode& node) override {
        auto mov = MovInstructionNode::create(node.return_expr->accept(*this),
                                              RegisterInstructionNode::create(RegisterInstructionNode::Register::W0));
        auto ret = ReturnInstructionNode::create();
        
        std::vector<AssemblerNode::PtrType> instructions;
        instructions.push_back(std::move(mov));
        instructions.push_back(std::move(ret));
        
        return CompoundAssemblerNode::create(std::move(instructions));
    }
    
    std::unique_ptr<AssemblerNode> visit(const UnaryTackyNode& node) override {
        auto src = node.src->accept(*this);
        auto dst = node.dst->accept(*this);
        
        auto mov = MovInstructionNode::create(std::move(src), std::move(dst));
        auto unary = UnaryInstructionNode::create(UnaryInstructionNode::Operator::Not, node.dst->accept(*this));
        
        std::vector<AssemblerNode::PtrType> instructions;
        instructions.push_back(std::move(mov));
        instructions.push_back(std::move(unary));
        
        return CompoundAssemblerNode::create(std::move(instructions));
    }
    
    std::unique_ptr<AssemblerNode> visit(const IntConstTackyNode& node) override {
        return LiteralInstructionNode::create(node.value);
    }
    
    std::unique_ptr<AssemblerNode> visit(const VarTackyNode& node) override {
        return PseudoRegister::create(node.var_name);
    }
};



};
