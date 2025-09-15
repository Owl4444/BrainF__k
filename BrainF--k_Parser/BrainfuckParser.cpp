#include <iostream>


#include "BrainfuckParser.h"

std::string BrainfuckParser::getSource()const {
	return source;
}

void BrainfuckParser::advance() {
	CurrentToken = lexer.nextToken();
}

bool BrainfuckParser::isCommand(TokenType type) {
	return
		type == INCREMENT || type == DECREMENT || type == MOVE_RIGHT ||
		type == MOVE_LEFT || type == OUTPUT || type == INPUT;
}


std::unique_ptr<CommandASTNode> BrainfuckParser::parseCommand() {
	if (isCommand(CurrentToken.token_type)) {
		TokenType type = CurrentToken.token_type;
		auto commandASTNode = std::make_unique<CommandASTNode>(type);
		advance(); // move to the next token
		return commandASTNode;
	}
	else {
		return nullptr;
	}
}

std::unique_ptr<ProgramASTNode> BrainfuckParser::parse() {
	auto program = std::make_unique<ProgramASTNode>();

	// startying with current token

	while (CurrentToken.token_type != END_OF_FILE) {
		// keep parsing
		auto statement = parseStatement();
		if (statement) {
			program->statements.push_back(statement.release());
		}
	}
	return program;
}


// parse either a command or a loop
std::unique_ptr<ASTNode> BrainfuckParser::parseStatement() {
	// Start of LOOP 
	if (CurrentToken.token_type == LOOP_START){
		auto loopASTNode = parseLoop();
		if (loopASTNode == nullptr) {
			std::cout << "Error parsing loop at position " << CurrentToken.position << std::endl;
		}
		else {
			return loopASTNode;
		}
	}
	else if (isCommand(CurrentToken.token_type)) {
		auto cmdASTNode = parseCommand();
		if (cmdASTNode == nullptr) {
			std::cout << "Error parsing token type " << CurrentToken.token_type <<  "at " << CurrentToken.position << std::endl;
		}
		else {
			return cmdASTNode;
		}
	}
	else {
		return nullptr;
	}

}



// parse a loop instruction  [...]
std::unique_ptr<LoopASTNode> BrainfuckParser::parseLoop() {

	if (CurrentToken.token_type != LOOP_START) {
		return nullptr; // not a loop start
	}

	advance();
	auto loopASTNode = std::make_unique<LoopASTNode>();

	// Keep sparsing statements
	while (CurrentToken.token_type != LOOP_END && CurrentToken.token_type != END_OF_FILE) {
		auto stmt = parseStatement();
		if (stmt) {
			loopASTNode->loop_body.push_back(stmt.release());
		}
	}

	if (CurrentToken.token_type == LOOP_END) {
		advance(); // consume the LOOP_END token
		return loopASTNode;
	}
	else
	{
		std::cout << "Error: Expected LOOP_END token at position " << CurrentToken.position << std::endl;
		return nullptr;
	}
		

}