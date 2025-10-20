// Copyright 2025 Yasser Zabuair.  See LICENSE for details.
#include <codegen/AssemblyGenerator.h>

namespace billiec::codegen {
std::vector<std::unique_ptr<AssemblerNode>> AssemblyGenerator::generate_assembly() {
    instructions.clear();
    
    auto curr_node = program_node->accept(*this);
    instructions.push_back(std::move(curr_node));
    
    return std::move(instructions);
}

std::unique_ptr<AssemblerNode> AssemblyGenerator::visit(const ProgramTackyNode& node) {
    return ProgramAssemblerNode::create(node.function_definition->accept(*this));
}

std::unique_ptr<AssemblerNode> AssemblyGenerator::visit(const FunctionTackyNode& node) {
    std::vector<std::unique_ptr<AssemblerNode>> instructions;
    
    for(const auto& curr_node: node.instructions) {
        instructions.push_back(curr_node->accept(*this));
    }
    
    return FunctionAssemblerNode::create(node.name, std::move(instructions));
}

std::unique_ptr<AssemblerNode> AssemblyGenerator::visit(const ReturnTackyNode& node) {    
    std::vector<AssemblerNode::PtrType> instructions;
    instructions.push_back(node.return_expr->accept(*this));
    instructions.push_back(ReturnInstructionNode::create());
    
    return CompoundAssemblerNode::create(std::move(instructions));
}

std::unique_ptr<AssemblerNode> AssemblyGenerator::visit(const UnaryTackyNode& node) {
    auto src = node.src->accept(*this);
    auto dst = node.dst->accept(*this);
    
    auto mov = MovInstructionNode::create(std::move(src), std::move(dst));
    auto unary = UnaryInstructionNode::create(UnaryInstructionNode::Operator::Not, node.dst->accept(*this));
    
    std::vector<AssemblerNode::PtrType> instructions;
    instructions.push_back(std::move(mov));
    instructions.push_back(std::move(unary));
    
    return CompoundAssemblerNode::create(std::move(instructions));
}

std::unique_ptr<AssemblerNode> AssemblyGenerator::visit(const IntConstTackyNode& node) {
    return LiteralInstructionNode::create(node.value);
}

std::unique_ptr<AssemblerNode> AssemblyGenerator::visit(const VarTackyNode& node) {
    return PseudoRegister::create(node.var_name);
}
} // namespace billiec::codegen
