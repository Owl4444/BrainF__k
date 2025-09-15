#include <cstring>
#include <iomanip> 

#include "BrainfuckInterpreter.h"
#include "ASTNode.h"

BrainfuckInterpreter::BrainfuckInterpreter() {
	reset();
}

BrainfuckInterpreter::~BrainfuckInterpreter() {
}

void BrainfuckInterpreter::reset() {
	// reset memory
	// reset location
	std::memset(tape, 0, TAPE_SIZE);
	pointer = 0;
	output.clear();
	input.clear();
	inputPointer = 0;
}

void BrainfuckInterpreter::visit(ProgramASTNode& node) {
	for(auto* stmt: node.statements){
		stmt->accept(*this);	
	}
} 


void BrainfuckInterpreter::print_tape(TokenType currentType) const {
	std::cout << tokenTypeToString(currentType) << " : Tape:\n";
	const int cellsPerRow = 16; 

	for (int i = 0; i < TAPE_SIZE; i++) {
		if (i % cellsPerRow == 0 && i != 0) {
			std::cout << "\n"; 
		}

		if (i == pointer) {
			std::cout << "[" << std::setw(3) << (int)tape[i] << "]";
		}
		else {
			std::cout << " " << std::setw(3) << (int)tape[i] << " ";
		}
	}
	std::cout << "\n\n";
}

void BrainfuckInterpreter::visit(CommandASTNode& node) {
	
	TokenType currCmd = node.getCommandTokenType();
	//print_tape(currCmd);

	switch (currCmd) {
	case INCREMENT:
		tape[pointer]++;
		break;
	case DECREMENT:
		tape[pointer]--;
		break;
	case MOVE_RIGHT:
		pointer++;
		if (pointer >= TAPE_SIZE) {
			std::cerr << "Error: Pointer moved beyond tape size\n";
			pointer = TAPE_SIZE - 1; // prevent overflow
		}
		break;
	case MOVE_LEFT:
		pointer--;
		if (pointer < 0) {
			std::cerr << "Error: Pointer moved before start of tape\n";
			pointer = 0; // prevent underflow
		}
		break;
	case OUTPUT:
		output += static_cast<char>(tape[pointer]);
		//std::cout << "Output: " << static_cast<char>(tape[pointer]) << "\n";
		std::cout << output << "\n";
		break;
	case INPUT:
		if (inputPointer < input.size()) {
			tape[pointer] = static_cast<unsigned char>(input[inputPointer]);
			inputPointer++;
		}
		else {
			std::cerr << "Error: No more input available\n";
			tape[pointer] = 0;
		}
		break;
	default:
		std::cerr << "Error: Unknown command\n";
		break;
	}
}

void BrainfuckInterpreter::visit(LoopASTNode& node) {
	//std::cout << "Entering Loop\n";
	while (tape[pointer] != 0) {
		//std::cout << "Looping, current cell value: " << (int)tape[pointer] << "\n";
		for (auto* stmt : node.loop_body) {
			stmt->accept(*this);
		}
	}
	//std::cout << "Exiting Loop\n";
}

std::string BrainfuckInterpreter::execute(ProgramASTNode& program, std::string& inputstring) {
	reset();
	input = inputstring;
	program.accept(*this);
	return output;

}