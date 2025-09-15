#pragma once
#include <string>
#include <utility>

#include "Token.h"

class BrainfuckLexer {

private:
	std::string source;
	size_t currPos;
public:
	BrainfuckLexer( std::string source) : source(std::move(source)) { currPos = 0; };
	Token nextToken();
	bool hasMoreTokens() const;
};