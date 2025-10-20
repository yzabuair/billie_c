// Copyright 2025 Yasser Zabuair.  See LICENSE for details.
#include <codegen/AssemblerPassPseudoRegister.h>

namespace billiec::codegen {

int AssemblerPassPseudoRegister::process() {
    // Look for all pseudo-registers and replace them with their offset.
    for(auto& curr_ins: instructions) {
        process_node_(curr_ins);
    }
    
    if (offsets.empty()) {
        return 0;
    }
    
    // This is how much we need to allocate on the stack.
    return offsets.size() * 4;
}

void AssemblerPassPseudoRegister::process_node_(AssemblerNode::PtrType& curr_node) {
    if(auto node = dynamic_cast<ProgramAssemblerNode*>(curr_node.get())) {
        visit_node_(*node);
    } else if (auto node = dynamic_cast<CompoundAssemblerNode*>(curr_node.get())) {
        visit_node_(*node);
    } else if (auto node = dynamic_cast<FunctionAssemblerNode*>(curr_node.get())) {
        visit_node_(*node);
    } else if (auto node = dynamic_cast<MovInstructionNode*>(curr_node.get())) {
        visit_node_(*node);
    }
}

void AssemblerPassPseudoRegister::visit_node_(CompoundAssemblerNode& node) {
    for(auto& curr_node: node.instructions) {
        process_node_(curr_node);
    }
}

void AssemblerPassPseudoRegister::visit_node_(ProgramAssemblerNode& node) {
    process_node_(node.function_definition);
}

void AssemblerPassPseudoRegister::visit_node_(FunctionAssemblerNode& node) {
    for(auto& curr_node: node.instructions) {
        process_node_(curr_node);
    }
}

void AssemblerPassPseudoRegister::visit_node_(MovInstructionNode& node) {
    PseudoRegister* pseudo_register = dynamic_cast<PseudoRegister*>(node.src.get());
    if (pseudo_register != nullptr) {
        int offset = get_offset_(pseudo_register->identifier);
        auto stack_ins = Stack::create(offset);
        node.src = std::move(stack_ins);
    }
    
    pseudo_register = dynamic_cast<PseudoRegister*>(node.dst.get());
    if (pseudo_register != nullptr) {
        int offset = get_offset_(pseudo_register->identifier);
        auto stack_ins = Stack::create(offset);
        node.dst = std::move(stack_ins);
    }
}

int AssemblerPassPseudoRegister::get_offset_(const std::string& pseudo_register) {
    if (offsets.empty()) {
        offsets.push_back(std::make_pair(pseudo_register, 0));
    } else {
        auto itr = std::find_if(std::begin(offsets), std::end(offsets), [&pseudo_register](const auto& curr) {
            if (curr.first == pseudo_register) {
                return true;
            }
            return false;
        });
        if (itr == std::end(offsets)) {
            int curr_offset = offsets.back().second;
            offsets.push_back(std::make_pair(pseudo_register, curr_offset+4));
        } else {
            return itr->second;
        }
    }
    
    return offsets.back().second;
}

} // namespace billiec::codegen
