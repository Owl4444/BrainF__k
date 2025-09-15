#include <iostream>
#include <string>
#include <vector>

#include "Token.h"
#include "BrainfuckLexer.h"
#include "ASTNode.h"
#include "ASTVisitor.h"
#include "BrainfuckInterpreter.h"


#include "BrainfuckParser.h"

int main() {

	std::string example_code = ">+<";

	/*
	    // Test Tokens
		std::vector<Token> tokens;
		tokens.emplace_back(MOVE_RIGHT, 0);
		tokens.emplace_back(INCREMENT, 1);


		for (auto& t : tokens) {
			std::cout << "Token type : " << t.token_type << " @ position: " << t.position << std::endl;
		}
		// End Test Tokens
	*/
	
	BrainfuckLexer lexer(example_code);

	/*
		Position: 0x0, TOKEN : 0x0
		Position: 0x1, TOKEN : 0x0
		Position: 0x2, TOKEN : 0x0
		Position: 0x3, TOKEN : 0x6
		Position: 0x4, TOKEN : 0x2
		Position: 0x5, TOKEN : 0x0
		Position: 0x6, TOKEN : 0x3
		Position: 0x7, TOKEN : 0x1
		Position: 0x8, TOKEN : 0x7
		Position: 0x9, TOKEN : 0x2
		Position: 0xa, TOKEN : 0x4
	*/
	while(lexer.hasMoreTokens()) {
		Token t = lexer.nextToken();
		std::cout << "Position: 0x"<< std::hex << t.position << ", TOKEN : 0x" << std::hex << t.token_type << std::endl;
	}


	
	
	// Testing Comman d node
	/*
	CommandASTNode commandASTNode(INCREMENT);
	std::cout << "Command Increment : " << commandASTNode.toString() << std::endl;
	CommandASTNode commandASTNode2(END_OF_FILE);
	std::cout << "Command EOF : " << commandASTNode2.toString() << std::endl;
	*/
	


	/*
ProgramASTNode program;
	program.statements.push_back(new CommandASTNode(INCREMENT));
	program.statements.push_back(new CommandASTNode(INCREMENT));
	program.statements.push_back(new CommandASTNode(LOOP_START));
	program.statements.push_back(new CommandASTNode(MOVE_RIGHT));

	program.statements.push_back(new CommandASTNode(DECREMENT));
	program.statements.push_back(new CommandASTNode(MOVE_LEFT));
	program.statements.push_back(new CommandASTNode(LOOP_END));

	std::cout << "PROGRAM DATA: " << program.toString();
	*/

	

	//BrainfuckParser parser(">++++++++[<+++++++++>-]<.>++++[<+++++++>-]<+.+++++++..+++.>>++++++[<+++++++>-]<+"
	//	"+ .------------. > ++++++[<++++++++ + >-]<+.<.++ + .------.--------.>> > ++++[<++++++++>-"
	//	"] < +.");


	// Testing Parser
	//BrainfuckParser parser("++++++++[>+++++++++<-]>.+++++++++++++++++++++++++++++.+++++++..+++.>++++[>++++++++<-]>.>+++++[<+++++++++++>-]<.>++++[<++++++>-]<.+++.------.--------.>+++[>+++++++++++<-]>.>++++++++++.");
	//BrainfuckParser parser(",.>,+.>,++.");
	//BrainfuckParser parser(">>>++++++++[<++++++++<++++++++<++++++++>>>-]..<+.<++.<+++.");
	//BrainfuckParser parser(">>>+[[-]>>[-]++>+>+++++++[<++++>>++<-]++>>+>+>+++++[>++>++++++<<-]+>>>,<++[[>[-> > ] < [>> ] << -]<[< ]<+>>[> ] > [<+>-[[<+>-]> ] < [[[-]< ] ++<-[<++++++++ + >[< -> - ] >> ] >> ] ] <<] < ] < [[< ]> [[> ]>> [>> ] + [<< ]<[< ]<+>>-] > [> ] + [-> > ]<<<< [[<< ]<[< ] + << [+> +<< -[> -- > +<< -[>+< [>> +<< -]]] > [<+>-] < ]++ >> -- > [> ] >> [>> ]] << [>> +< [[< ]< ] > [[<< ]<[< ] + [-<+>> -[<< +> ++ > -[< ->[<< +>> -]]]<[> +< -]>]>[> ] > ] > [>> ] >> ] << [>> +>> +>> ] << [->>>>>>> > ] << [> .>>>>>> > ] << [> ->>>>>] << [> , >> > ] << [> +> ] << [+<< ] < ] ");
	
	// Fib from https://brainfuck.org/
	BrainfuckParser parser("> ++++++++++ > +> +[[++++ + [> ++++++++ < -] > . < ++++++[> -------- < -] + << < ]> . >> [[-]<[> +< -] >> [<< +> +> -]<[> +< -[> +< -[> +< -[> +< -[> +< -[> +< -[> +< -[> +< -[> +< -[> [-] > +> +<< < -[> +< -]]]]]]]]]]] + >> >] << <]");


	std::cout << "Parser containing soruce " << parser.getSource() << std::endl;
	auto  program = parser.parse();
	std::cout << "Parsed program: " << program->toString() << std::endl;


	// Testing Interpreter with parser
	BrainfuckInterpreter interpreter;
	std::string input = "AAA";  // No input needed for this program

	std::string result = interpreter.execute(*program, input);
	
	std::cout << "Output: " << result << std::endl;



	


	return -1;
} 