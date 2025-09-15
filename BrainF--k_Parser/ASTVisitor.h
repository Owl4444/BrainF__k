#pragma once
#include <iostream>

// Include the full definitions of CommandASTNode and ProgramASTNode


class ProgramASTNode;
class CommandASTNode;
class LoopASTNode;

class ASTVisitor {
public:
    virtual void visit(ProgramASTNode& node) = 0;
    virtual void visit(CommandASTNode& node) = 0;
    virtual void visit(LoopASTNode& node) = 0;
    virtual ~ASTVisitor() = default;
};

