//Syntax analysis for brackets
#include <iostream>
#include <stdio.h>
#include <fstream>

//Global variables
int depth = 0; //recursive depth
std::ofstream interData("Data.txt", std::ofstream::out);
std::ofstream output("output.txt", std::ofstream::out);
enum error_code {EMPTY, EXCESS, INVALID_SC, MISS_S_CL, MISS_S, MISS_R_CL, MISS_R, MISS_F_CL, MISS_F};
enum internal_op_code {ERROR, ENTER_B, EXIT_B, ENTER_S, EXIT_S, ENTER_R, EXIT_R, ENTER_F, EXIT_F};

//Function definitions
void error(error_code code); 				//Displays error message
void interDataGen(internal_op_code op_code);//Fills file Data.txt with intermediate data (algorithm work)
void displayFileContents(); 				//Displays input file contents

bool isBracket(); 		//Bracket ::= Square | Round | Figure
bool isSquare(); 		//Square  ::= [Round Figure]  | +
bool isRound(); 		//Round   ::= (Figure Square) | -
bool isFigure(); 		//Figure  ::= {Square Round}  | 0

//Function implementations
bool isBracket(){
	interDataGen(ENTER_B);
	char c;
	c = std::cin.get();
	std::ungetc(c, stdin);
	if(c == '[' || c == '+'){ return isSquare(); }
	if(c == '(' || c == '-'){ return isRound();  }
	if(c == '{' || c == '0'){ return isFigure(); }
	std::cout << c;
	output << c;
    error(INVALID_SC);
	return 0;
}

bool isSquare(){
	depth++;
	interDataGen(ENTER_S);

	if(!std::cin.eof()){
			char input;
			input = std::cin.get();
			std::cout << input;
			output << input;

			if(input == '+'){
				interDataGen(EXIT_S);
				depth--;
				return 1;
			}

			if(input == '['){
				if(isRound()){
					if(isFigure()){
						if(!std::cin.eof()){
							input = std::cin.get();
							std::cout << input;
							output << input;
							if(input==']'){
								interDataGen(EXIT_S);
								depth--;
								return 1;
							} else error(MISS_S_CL); // "]" is missing
						}
					}
				}
			} else error(MISS_S); // "[" or "+" is missing
		}

	interDataGen(EXIT_S);
	depth--;
	return 0;
}

bool isRound(){
	depth++;
	interDataGen(ENTER_R);

	if(!std::cin.eof()){
			char input;
			input = std::cin.get();
			std::cout << input;
			output << input;

			if(input == '-'){
				interDataGen(EXIT_R);
				depth--;
				return 1;
			}

			if(input == '('){
				if(isFigure()){
					if(isSquare()){
						if(!std::cin.eof()){
							input = std::cin.get();
							std::cout << input;
							output << input;
							if(input==')'){
								interDataGen(EXIT_R);
								depth--;
								return 1;
							} else error(MISS_R_CL); // ")" is missing
						}
					}
				}
			} else error(MISS_R); // "-" or "(" is missing
		}

	interDataGen(EXIT_R);
	depth--;
	return 0;
}

bool isFigure(){
	depth++;
	interDataGen(ENTER_F);

	if(!std::cin.eof()){
			char input;
			input = std::cin.get();
			std::cout << input;
			output << input;

			if(input == '0'){
				interDataGen(EXIT_F);
				depth--;
				return 1;
			}

			if(input == '{'){
				if(isSquare()){
					if(isRound()){
						if(!std::cin.eof()){
							input = std::cin.get();
							std::cout << input;
							output << input;
							if(input=='}'){
								interDataGen(EXIT_F);
								depth--;
								return 1;
							} else error(MISS_F_CL); // "}" is missing
						}
					}
				}
			} else error(MISS_F); // "0" or "{" is missing
		}

	interDataGen(EXIT_F);
	depth--;
	return 0;
}

void error(error_code code){
	interDataGen(ERROR);
	switch(code){
	case EMPTY: std::cout << "!-Empty input.";
			output << "!-Empty input.";
			break;
	case EXCESS: std::cout << "\n!-Excess characters.\nThis is not a Bracket.";
			output << "\n!-Excess characters.\nThis is not a Bracket.";
			break;
	case INVALID_SC: std::cout << "\n!-Invalid starting character.";
			output << "\n!-Invalid starting character.";
			break;
	case MISS_S_CL: std::cout << "\n!-']' is missing.";
			output << "\n!-']' is missing.";
			break;
	case MISS_S: std::cout << "\n!-'[' or '+' is missing.";
			output << "\n!-'[' or '+' is missing.";
			break;
	case MISS_R_CL: std::cout << "\n!-')' is missing.";
			output << "\n!-')' is missing.";
			break;
	case MISS_R: std::cout << "\n!-'(' or '-' is missing.";
			output << "\n!-'(' or '-' is missing.";
			break;
	case MISS_F_CL: std::cout << "\n!-'}' is missing.";
			output << "\n!-'}' is missing.";
			break;
	case MISS_F: std::cout << "\n!-'{' or '0' is missing.";
			output << "\n!-'{' or '0' is missing.";
			break;
	default: break;
	}
}

void interDataGen(internal_op_code op_code){
	interData << "Depth: " << std::dec << depth << ".\t";
	for(int i = 0; i < depth; i++) interData << ".\t";
	switch(op_code){
	case ERROR: interData << "INVALID INPUT\n"; break;
	case ENTER_B: interData << "Entering BRACKET\n"; break;
	case EXIT_B: interData << "Exiting BRACKET\n"; break;
	case ENTER_S: interData << "Entering SQUARE\n"; break;
	case EXIT_S: interData << "Exiting SQUARE\n"; break;
	case ENTER_R: interData << "Entering ROUND\n"; break;
	case EXIT_R: interData << "Exiting ROUND\n"; break;
	case ENTER_F: interData << "Entering FIGURE\n"; break;
	case EXIT_F: interData << "Exiting FIGURE\n"; break;
	}
}

void displayFileContents(){
	std::cout << "File contents:\n";
	std::cout << "-begin-\n";
	char c;
	c = std::cin.get();
	while(!std::cin.eof()){
		std::cout << c;
		c = std::cin.get();
	}
	std::cout << "\n-end-\n";
}

int main(int argc, char* argv[]){
	if(argc == 2){ //true: input from file. false: input from console
		std::cout << "The program is launched in file input mode.\n";

		std::freopen(argv[1], "r", stdin);

		displayFileContents();

		//reset input stream
		std::cin.clear();
		rewind(stdin);
	} else { //input from console
		std::cout << "The program is launched in console input mode.\n";
		std::cout << "To launch a program in file input mode, drag input file on executable file, or pass a path to input file as an argument (if launching from terminal/console).\n";
		std::cout << "Enter a string of characters to start a syntax analysis for Brackets:\n";
		}
		
	char c = std::cin.get();
	if(std::cin.eof() || (c == '\n' && argc != 2)){ //true: empty input. false: input is not empty
		error(EMPTY);
	} else { //input is not empty, proceed.
		std::ungetc(c, stdin);
		if (isBracket()){
			interDataGen(EXIT_B);
			c = std::cin.get();
			if((!std::cin.eof() && argc == 2) || (c !='\n' && argc != 2)) {//true: there is one or more characters left in input stream. false: end of input.
				std::cout << c;
				output << c;
				error(EXCESS);
				} else {
				std::cout << "\nThis is a Bracket";
				output << "\nThis is a Bracket";
			}
		}
		else{
			interDataGen(EXIT_B);
			std::cout << "\nThis is not a Bracket";
			output << "\nThis is not a Bracket";
		}
	}

	if(argc == 2)
		fclose(stdin);

	std::cout << '\n';
	#ifdef _WIN32
	std::freopen("CONIN$", "r", stdin);
	system("PAUSE");
	#endif
	
	interData.close();
	output.close();
	return 0;
}