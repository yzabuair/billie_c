// Copyright 2025 Yasser Zabuair.  See LICENSE for details.
#include <codegen/AssemblerPassFixInstructions.h>

namespace billiec::codegen {
void AssemblerPassFixInstructions::process() {
    for(auto& curr_node: instructions) {
        process_node_(curr_node);
    }
}

void AssemblerPassFixInstructions::process_node_(AssemblerNode::PtrType& curr_node) {
    if(auto node = dynamic_cast<ProgramAssemblerNode*>(curr_node.get())) {
        visit_node_(*node);
    } else if (auto node = dynamic_cast<CompoundAssemblerNode*>(curr_node.get())) {
        visit_node_(*node);
    } else if (auto node = dynamic_cast<FunctionAssemblerNode*>(curr_node.get())) {
        curr_func = node;
        visit_node_(*node);
    } else if (auto node = dynamic_cast<MovInstructionNode*>(curr_node.get())) {
        visit_node_(node);
    }
}

void AssemblerPassFixInstructions::visit_node_(CompoundAssemblerNode& node) {
    for(auto& ins: node.instructions) {
        process_node_(ins);
    }
}

void AssemblerPassFixInstructions::visit_node_(ProgramAssemblerNode& node) {
    process_node_(node.function_definition);
}

void AssemblerPassFixInstructions::visit_node_(FunctionAssemblerNode& node) {
    // Stick a stack allocation at the start.
    auto allocate_stack = AllocateStackInstructionNode::create(stack_size);
    node.instructions.insert(std::begin(node.instructions), std::move(allocate_stack));
    
    // And de-allocate at the end, before the return.
    for(auto itr = std::end(node.instructions)-1; itr != std::begin(node.instructions); --itr) {
        if (check_ret_node_(node.instructions, itr)) {
            break;
        }
        
        auto compound_node = dynamic_cast<CompoundAssemblerNode*>(itr->get());
        if (compound_node != nullptr) {
            for(auto itr2 = std::begin(compound_node->instructions); itr2 != std::end(compound_node->instructions); ++itr2) {
                if (check_ret_node_(compound_node->instructions, itr2)) {
                    break;
                }
            }
        }
    }
}

bool AssemblerPassFixInstructions::check_ret_node_(std::vector<AssemblerNode::PtrType>& instructions,
                                                   std::vector<AssemblerNode::PtrType>::iterator itr) {
    auto ret_node = dynamic_cast<ReturnInstructionNode*>(itr->get());
    if (ret_node != nullptr) {
        auto deallocate_stack = DeAllocateStackInstructionNode::create(stack_size);
        instructions.insert(itr, std::move(deallocate_stack));
        return true;
    }
    return false;
}

void AssemblerPassFixInstructions::visit_node_(MovInstructionNode* node) {
    // Find the instruction that this corresponds in the "current" function.
    if (curr_func == nullptr) {
        // TODO: Error..
    }
    
    auto find_lambda = [node](const std::vector<AssemblerNode::PtrType>& ins) {
        auto itr = std::find_if(std::begin(ins), std::end(ins), [node](const auto& curr) {
            if (curr.get() == node) {
                return true;
            }
            return false;
        });
        
        return itr;
    };
    
    // Check the current function.
    bool found = false;
    auto itr = find_lambda(curr_func->instructions);
    if (itr == std::end(curr_func->instructions)) {
        // Also check in compound nodes.
        for(auto itr2 = std::begin(curr_func->instructions); itr2 != std::end(curr_func->instructions); ++itr2) {
            auto compound = dynamic_cast<CompoundAssemblerNode*>(itr2->get());
            if (compound != nullptr) {
                itr = find_lambda(compound->instructions);
                if (itr != std::end(compound->instructions)) {
                    found = true;
                    break;
                }
            }
        }
    } else {
        found = true;
    }
    
    if (!found) {
        // TODO: Error..
    }
    
    // Check if there's any local stack vars.
    auto mov_ins = dynamic_cast<MovInstructionNode*>(itr->get());
    if (mov_ins == nullptr) {
        // TODO: Error.
    }
    
    // Check if source or dest are pseudo-registers and replace with the appropriate instructions.
    std::vector<AssemblerNode::PtrType> instructions;
    auto src_stack = dynamic_cast<PseudoRegister*>(mov_ins->src.get());
    if (src_stack != nullptr) {
        
    }
    
    auto dst_stack = dynamic_cast<PseudoRegister*>(mov_ins->src.get());
    if (dst_stack != nullptr) {
        
    }
    
    
    
    
    // Replace the instruction with a compound instruction.
//    std::vector<AssemblerNode::PtrType> instructions;
//    instructions.push_back(
    
}

} // namespace billiec::codegen
