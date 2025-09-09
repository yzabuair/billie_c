// Copyright 2025 Yasser Zabuair.  See LICENSE for details.
#pragma once

#include <codegen/AssemblerAst.h>
#include <parser/Ast.h>

#include <any>
#include <map>
#include <vector>

namespace billiec::codegen {

class AssemblyGenerator: public parser::AstVisitor {
    parser::AstNode::PtrType program_node_;
    ProgramAssemblerNode::PtrType program_node_assembly_;
    FunctionAssemblerNode::PtrType function_node_assembly_;
    std::string curr_func_;
    std::map<std::string, std::vector<std::unique_ptr<AssemblerNode>>> instructions_;
    LiteralInstructionNode::PtrType curr_literal_;
    
public:
    AssemblyGenerator(parser::AstNode::PtrType program_node):
        program_node_{std::move(program_node)} {
        
    }
    
    ProgramAssemblerNode::PtrType generate_assembler() {
        program_node_->accept(*this);
        return std::move(program_node_assembly_);
    }
    
    std::any visit(const parser::ProgramNode& node) override {
        return std::any{ProgramAssemblerNode::create(std::any_cast<FunctionAssemblerNode::PtrType>(node.function_definition->accept(*this)))};
    }
    
    std::any visit(const parser::FunctionNode& node) override {
        curr_func_ = node.name.lexeme;
        for(const auto& curr_ast: node.body) {
            curr_ast->accept(*this);
        }
        auto instructions = std::move(instructions_[curr_func_]);
        function_node_assembly_ = FunctionAssemblerNode::create(node.name, std::move(instructions));
    }
    
    void visit(const parser::ReturnNode& node) override {
        if (node.return_expr) {
            node.return_expr->accept(*this);
            
            // Whatever is the literal that results from this, we set this as the return value.
            auto mov_instruction = MovInstructionNode::create(std::move(curr_literal_),
                                                              RegisterInstructionNode::create(RegisterInstructionNode::Register::W0));
            instructions_[curr_func_].push_back(std::move(mov_instruction));
        }
        auto return_node = ReturnInstructionNode::create();
        instructions_[curr_func_].push_back(std::move(return_node));
    }
    
    void visit(const parser::UnaryNode& node) override {
        
    }
    
    void visit(const parser::LiteralNode& node) override {
        curr_literal_ = LiteralInstructionNode::create(node.value);
    }
};

};
