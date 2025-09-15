#pragma once

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

/* TOKEN SHOULD BE ABLE TO HOLD TOKEN TYPE AND POSITION */
struct Token {
	TokenType token_type;
	size_t position;

	// Constructor 
	Token(TokenType t, size_t pos) :token_type(t), position(pos) {}
};

static std::string tokenTypeToString(TokenType type) {
	switch (type) {
	case INCREMENT: return "INCREMENT";
	case DECREMENT: return "DECREMENT";
	case MOVE_RIGHT: return "MOVE_RIGHT";
	case MOVE_LEFT: return "MOVE_LEFT";
	case OUTPUT: return "OUTPUT";
	case INPUT: return "INPUT";
	case LOOP_START: return "LOOP_START";
	case LOOP_END: return "LOOP_END";
	case END_OF_FILE: return "END_OF_FILE";
	default: return "UNKNOWN";
	}
}