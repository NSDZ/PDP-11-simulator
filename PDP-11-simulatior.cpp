//============================================================================
// Name        : TP.cpp
// Author      : Nassim sbaihia
// Version     :
// Copyright   : --
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
#include "Repertoire.h"

//


using namespace std;

//instruction types

set <string> twoOperands = {"ADD", "MOV", "CMP", "MUL", "DIV"};

set <string> oneOperand = {
		"INC", "DEC", "CLR",
		"BR", "BGT", "BGE", "BLT", "BLE", "BEQ", "BNE"
};


//program memory

vector <Instruction> program;

int CO = 0;

//Registres & variables memory;

map <string, int> memory;

map <string, int> labels;




int main() {


	//inserting PDP11 7 registres

	memory.insert(make_pair("R0", 0));
	memory.insert(make_pair("R1", 0));
	memory.insert(make_pair("R2", 0));
	memory.insert(make_pair("R3", 0));
	memory.insert(make_pair("R4", 0));
	memory.insert(make_pair("R5", 0));
	memory.insert(make_pair("R6", 0));
	memory.insert(make_pair("R7", 0));
	//memory.insert(make_pair("CMP", 0));


	//pdp11


	printf("\t  _____  _____  _____    __ __  \n");
	printf("\t |  __ \\|  __ \\|  __ \\  /_ /_ |  C\n");
	printf("\t | |__) | |  | | |__) |  | || |  O\n");
	printf("\t |  ___/| |  | |  ___/   | || |  D\n");
	printf("\t | |    | |__| | |_      | || |  E\n");
	printf("\t |_|    |_____/|_(_)     |_||_|  D  by Nassim sbaihia | @nsm\n\n\n\n");


	//reading the program to be exxcuted
	scanProgram();

	int ram = memory["R7"];
	printf("\n\nyour program is saved in memory, here's it: \n\n");
	for(auto x:program) {
		printf("  @%d: \t", ram++);
		printInstruction(x);
		printf("\n");
	}



	printf("\n\nEnter a specefic Registre or variable to check at excution time: ");
	string mva;
//EM:
	cin >> mva;
/*	if(!memory.count(mva)) {
		printf("INVALID INPUT, theres no %s in memory, please enter a valide one again: ", mva.c_str());
		goto EM;
	} */



	printf("\n\nExcution table:\n\n");


	printStart(mva);

	int phase = 0;
	for(CO = 0; CO < program.size() && program[CO-1].code != "Halt" && phase < 100; CO++) {

		string instruction = program[CO].code + " " + program[CO].operand1 + (twoOperands.count(program[CO].code) == 1 ? "," : " ") + program[CO].operand2;
		string RM = instruction;


		//DCR
		int RA = CO+memory["R7"];
		printThirdLine();
		printf("\u2551 DCR %-4d \u2551 %-6d \u2551 %-6d \u2551 %-19s \u2551\ %-19s \u2551 %-6d \u2551\n\t", phase, CO+memory["R7"], RA, instruction.c_str(), instruction.c_str(), memory[mva]);

		//FCR
		printThirdLine();
		printf("\u2551 FCR %-4d \u2551 %-6d \u2551 %-6d \u2551 %-19s \u2551\ %-19s \u2551 %-6d \u2551\n\t", phase, CO+1+memory["R7"], RA, instruction.c_str(), instruction.c_str(), memory[mva]);


		//excuting instructions

		if(program[CO].code == "ADD")
			ADD(program[CO]);

		else if(program[CO].code == "CMP")
			CMP(program[CO]);

		else if(program[CO].code == "MOV")
			MOV(program[CO]);

		else if(program[CO].code == "MUL")
			MUL(program[CO]);

		else if(program[CO].code == "DIV")
			DIV(program[CO]);

		else if(program[CO].code == "CLR")
			CLR(program[CO]);

		else if(program[CO].code == "DEC")
			DEC(program[CO]);

		else if(program[CO].code == "INC")
			INC(program[CO]);

		else if(program[CO].code == "BR")
			BR(program[CO]);

		else if(program[CO].code == "BGT")
			BGT(program[CO]);

		else if(program[CO].code == "BGE")
			BGE(program[CO]);

		else if(program[CO].code == "BLT")
			BLT(program[CO]);

		else if(program[CO].code == "BLE")
			BLE(program[CO]);

		else if(program[CO].code == "BEQ") {
			BEQ(program[CO]);
		}

		else if(program[CO].code == "BNE")
					BNE(program[CO]);

		//else
			//printf("ER0R");

		if( program[CO].code == "CMP" || program[CO].code == "MOV" || program[CO].code == "ADD" || program[CO].code == "MUL" || program[CO].code == "DIV" || program[CO].code == "SUB") {

			printThirdLine();
			printf("\u2551 FCE %-4d \u2551 %-6d \u2551 %-6d \u2551 %-19s \u2551\ %-19d \u2551 %-6d \u2551\n\t", phase, CO+1+memory["R7"], RA, instruction.c_str(), operandToInt(program[CO].operand2), memory[mva]);


		} else {
			//FCE
			printThirdLine();
			printf("\u2551 FCE %-4d \u2551 %-6d \u2551 %-6d \u2551 %-19s \u2551\ %-19s \u2551 %-6d \u2551\n\t", phase, CO+1+memory["R7"], RA, instruction.c_str(), instruction.c_str(), memory[mva]);
			//printThirdLine();
		}



		phase++;

	}

	//the end of excution table
	printEnd();


	//printf("\n %d", memory["CMP"]);






	return 0;
}
