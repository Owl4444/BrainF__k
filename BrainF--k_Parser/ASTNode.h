

#pragma once
#include <string>
#include <vector>

#include "Token.h"

class DummyVisitors;
class ASTVisitor;
class CommandASTNode;
class LoopASTNode;

class ASTNode {
public:
	virtual ~ASTNode() = default;
	virtual std::string toString() = 0;

	// Preparing for visitor to visit
	virtual void accept(ASTVisitor& visitor) = 0;
};


class CommandASTNode : public ASTNode {
public:

	CommandASTNode(TokenType commandType) : command(commandType) {}
	std::string toString() override;
	void accept(ASTVisitor& visitor) override;
	TokenType getCommandTokenType() const { return command; }

private:
	TokenType command;
};

class ProgramASTNode : public ASTNode {
public:
	std::vector<ASTNode*> statements;
	std::string toString() override; 
	
	void accept(ASTVisitor& visitor) override;

	~ProgramASTNode() {
		for (auto* stmt : statements) {
			delete stmt;
		}
	}

	// private:
	//	TokenType command;
};

class LoopASTNode : public ASTNode {
public:	
	std::vector<ASTNode*> loop_body;

	void accept(ASTVisitor& visitor) override;


	std::string toString() override {
		std::string output = "[ ";
		for (auto& stmt : loop_body) {
			output += stmt->toString();
			output += " ";
		}
		output += "]";
		return output;
	}
	~LoopASTNode() {
		for (auto* stmt : loop_body) {
			delete stmt;
		}
	}



	

		
	
		
};