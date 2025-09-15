#include "BrainfuckLexer.h"
#include "Token.h"

/*
enum TokenType {
	INCREMENT, // +
	DECREMENT, // -
	MOVE_RIGHT, // >
	MOVE_LEFT, // <
	OUTPUT, // .
	INPUT, // ,
	LOOP_START, // [
	LOOP_END, // ]
	END_OF_FILE // EOF
};
*/
Token BrainfuckLexer::nextToken() {
	while (currPos < source.length()) {
		char currentChar = source[currPos];
		// do the scan
		if (source[currPos] == ' ' || source[currPos] == '\t' || source[currPos] == '\r' || source[currPos] == '\n') {
			currPos++;
			continue;
		}
		else if (currentChar == '+') { currPos++; return Token(INCREMENT, currPos-1); }
		else if (currentChar == '-') { currPos++; return Token(DECREMENT, currPos - 1); }
		else if (currentChar == '[') { currPos++; return Token(LOOP_START, currPos - 1); }
		else if (currentChar == ']') { currPos++; return Token(LOOP_END, currPos - 1); }
		else if (currentChar == '>') { currPos++; return Token(MOVE_RIGHT, currPos - 1); }
		else if (currentChar == '<') { currPos++; return Token(MOVE_LEFT, currPos - 1); }
		else if (currentChar == '.') { currPos++; return Token(OUTPUT, currPos - 1); }
		else if (currentChar == ',') { currPos++; return Token(INPUT, currPos - 1); }
		else { currPos++; continue; }
	}

	// After all the characters are scanned, return the EOF
	return Token(END_OF_FILE, currPos);
}

bool BrainfuckLexer::hasMoreTokens() const {
	return source.length() > currPos;
}
