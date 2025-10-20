// Copyright 2025 Yasser Zabuair.
#pragma once

#include <scanner/Token.h>

#include <iostream>
#include <memory>
#include <vector>

namespace billiec::codegen {

// Forwards
struct CompoundAssemblerNode;
struct ProgramAssemblerNode;
struct FunctionAssemblerNode;
struct MovInstructionNode;
struct ReturnInstructionNode;
struct LiteralInstructionNode;
struct RegisterInstructionNode;
struct UnaryInstructionNode;
struct AllocateStack;
struct PseudoRegister;


// ---


struct AssemblerNode {
    using PtrType = std::unique_ptr<AssemblerNode>;
    
    AssemblerNode() = default;
    virtual ~AssemblerNode() = default;
};


// ---

struct CompoundAssemblerNode: public AssemblerNode {
    using PtrType = std::unique_ptr<CompoundAssemblerNode>;
    std::vector<AssemblerNode::PtrType> instructions;
    
    CompoundAssemblerNode(std::vector<AssemblerNode::PtrType> instructions):
        instructions{std::move(instructions)} {
        
    }
    
    static PtrType create(std::vector<AssemblerNode::PtrType> instructions) {
        return std::make_unique<CompoundAssemblerNode>(std::move(instructions));
    }
};

// ---

struct ProgramAssemblerNode: public AssemblerNode {
    using PtrType = std::unique_ptr<ProgramAssemblerNode>;
    std::unique_ptr<AssemblerNode> function_definition;
    
    ProgramAssemblerNode(std::unique_ptr<AssemblerNode> function_definition):
        function_definition{std::move(function_definition)} {
    }
    
    static PtrType create(std::unique_ptr<AssemblerNode> function_definition) {
        return std::make_unique<ProgramAssemblerNode>(std::move(function_definition));
    }
};

// ---

struct FunctionAssemblerNode: public AssemblerNode {
    using PtrType = std::unique_ptr<FunctionAssemblerNode>;
    scanner::Token name;
    std::vector<std::unique_ptr<AssemblerNode>> instructions;
    
    FunctionAssemblerNode(const scanner::Token& name,
                 std::vector<std::unique_ptr<AssemblerNode>> instructions):
        name{name},
        instructions{std::move(instructions)} {
        
    }
    
    static PtrType create(const scanner::Token name,
                   std::vector<std::unique_ptr<AssemblerNode>> instructions) {
        return std::make_unique<FunctionAssemblerNode>(name, std::move(instructions));
    }
};

// --

struct MovInstructionNode: public AssemblerNode {
    using PtrType = std::unique_ptr<MovInstructionNode>;
    std::unique_ptr<AssemblerNode> src;
    std::unique_ptr<AssemblerNode> dst;
    
    MovInstructionNode(std::unique_ptr<AssemblerNode> src,
                       std::unique_ptr<AssemblerNode> dst):
        src{std::move(src)},
        dst{std::move(dst)} {
        
    }
    
    static PtrType create(std::unique_ptr<AssemblerNode> src,
                          std::unique_ptr<AssemblerNode> dst) {
        return std::make_unique<MovInstructionNode>(std::move(src), std::move(dst));
    }
};

// --

struct ReturnInstructionNode: public AssemblerNode {
    using PtrType = std::unique_ptr<ReturnInstructionNode>;
    
    ReturnInstructionNode() {
        
    }
    
    static PtrType create() {
        return std::make_unique<ReturnInstructionNode>();
    }
};

// ---

struct LiteralInstructionNode: public AssemblerNode {
    using PtrType = std::unique_ptr<LiteralInstructionNode>;
    scanner::TokenValueType value;
    
    LiteralInstructionNode(const scanner::TokenValueType& value):
        value{value} {
        
    }
    
    static PtrType create(const scanner::TokenValueType& value) {
        return std::make_unique<LiteralInstructionNode>(value);
    }
};

// ---

struct RegisterInstructionNode: public AssemblerNode {
    using PtrType = std::unique_ptr<RegisterInstructionNode>;
    
    enum class Register {
        W0 = 0
    };
    Register which_register;
    
    RegisterInstructionNode(Register which_register):
        which_register{which_register} {
    }
    
    static PtrType create(Register which_register) {
        return std::make_unique<RegisterInstructionNode>(which_register);
    }
};

// ---

struct UnaryInstructionNode: public AssemblerNode {
    using PtrType = std::unique_ptr<UnaryInstructionNode>;
    
    enum class Operator {
        Neg = 0,
        Not = 1
    };
    Operator unary_operator;
    AssemblerNode::PtrType operand;
    
    UnaryInstructionNode(Operator unary_operator,
                         AssemblerNode::PtrType operand):
        unary_operator{unary_operator},
        operand{std::move(operand)} {
    }
    
    static PtrType create(Operator unary_operator,
                          AssemblerNode::PtrType operand) {
        return std::make_unique<UnaryInstructionNode>(unary_operator, std::move(operand));
    }
};

// ---

struct AllocateStackInstructionNode: public AssemblerNode {
    using PtrType = std::unique_ptr<AllocateStackInstructionNode>;
    int size{0};
    
    AllocateStackInstructionNode(int size): size{size} {
        
    }
    
    static PtrType create(int size) {
        return std::make_unique<AllocateStackInstructionNode>(size);
    }
};

// ---

struct DeAllocateStackInstructionNode: public AssemblerNode {
    using PtrType = std::unique_ptr<DeAllocateStackInstructionNode>;
    int size{0};
    
    DeAllocateStackInstructionNode(int size): size{size} {
        
    }
    
    static PtrType create(int size) {
        return std::make_unique<DeAllocateStackInstructionNode>(size);
    }
};

// ---

struct PseudoRegister: public AssemblerNode {
    using PtrType = std::unique_ptr<PseudoRegister>;
    std::string identifier;
    
    PseudoRegister(const std::string& identifier): identifier{identifier} {
    }
    
    static PtrType create(const std::string& identifier) {
        return std::make_unique<PseudoRegister>(identifier);
    }
};

// ---

struct Stack: public AssemblerNode {
    using PtrType = std::unique_ptr<Stack>;
    int offset{0};
    
    Stack(int offset): offset{offset} {
    }
    
    static PtrType create(int offset) {
        return std::make_unique<Stack>(offset);
    }
};

// ---

struct StoreInstructionNode: public AssemblerNode {
    using PtrType = std::unique_ptr<StoreInstructionNode>;
    int stack_offset;
    
    StoreInstructionNode(int offset): stack_offset{offset} {
    }
    
    static PtrType create(int offset) {
        return std::make_unique<StoreInstructionNode>(offset);
    }
    
};


} // namespace billiec::codegen
