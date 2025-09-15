#pragma once

#include<string>
#include<utility>
#include <memory>

#include "BrainfuckLexer.h"
#include "Token.h"
#include "ASTNode.h"


class BrainfuckParser { 

public:
	
	std::unique_ptr<ProgramASTNode> parse(); // shoudl return programASTNode which should hold statements (grammar in play here)

	BrainfuckParser(std::string source): source(source), lexer(source),CurrentToken(END_OF_FILE, 0){
		advance();
	}


	std::string getSource() const;
	void advance(); // get the next token
	bool isCommand(TokenType); // check if command instruction
	std::unique_ptr<CommandASTNode> parseCommand(); // parse a single command instruction
	std::unique_ptr<LoopASTNode> parseLoop(); // parse a loop instruction  [...]
	std::unique_ptr<ASTNode> parseStatement(); // parse either a command or a loop
	
private:
	BrainfuckLexer lexer;
	std::string source;
	Token CurrentToken;
};