#pragma once

#include "ASTVisitor.h"
#include "Token.h"

class BrainfuckInterpreter : public ASTVisitor {

public:

	BrainfuckInterpreter();
	~BrainfuckInterpreter();

	// reset interpreter state
	void reset();
	void print_tape(TokenType currentType) const;

	void visit(ProgramASTNode& node) override;
	void visit(CommandASTNode& node) override;
	void visit(LoopASTNode& node) override;

	std::string execute(ProgramASTNode& program, std::string& inputstring);

	std::string getOutput() const {
		return output;
	}
private:
	static const int TAPE_SIZE = 30000;
	unsigned char tape[TAPE_SIZE];
	int pointer;

	// For I/O
	std::string output;
	std::string input;
	size_t inputPointer;

};