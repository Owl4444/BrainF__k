#include <iostream>

#include "Token.h"

#include "ASTNode.h"
#include "ASTVisitor.h"

std::string CommandASTNode::toString() {
	switch (command) {
	case INCREMENT:return "+";
	case DECREMENT: return "-";
	case MOVE_RIGHT:return ">";
	case MOVE_LEFT: return "<";
	case LOOP_END:return "]";
	case LOOP_START: return "[";
	case INPUT:return ",";
	case OUTPUT: return ".";
	default: return "?";
	}
}

std::string ProgramASTNode::toString() {
	std::string output;
	for (auto& stmt : statements) {
		output += stmt->toString();
		output += " ";
	}
	return output;
}


void CommandASTNode::accept(ASTVisitor& visitor)  {
	visitor.visit(*this);
}
void ProgramASTNode::accept(ASTVisitor& visitor)  {
	visitor.visit(*this);
}

void LoopASTNode::accept(ASTVisitor& visitor)  {
	visitor.visit(*this);
}
