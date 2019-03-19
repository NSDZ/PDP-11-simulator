#include <bits/stdc++.h>
#include "Repertoire.h"

using namespace std;

//function to read input

void scanProgram() {
	string tmp;
	int vars = 0, i = 0;

	printf("enter a the @dress of the first instruction: ");
	cin >> memory["R7"];
	printf("\nenter a valid program please: \n");
	while(cin>>tmp && tmp != "Halt") {
		Instruction ins;
		char str[10];
		//int i = 0;
		if(!oneOperand.count(tmp) && !twoOperands.count(tmp)) {
			ins.label = tmp;
			labels.insert(make_pair(tmp,i));
			cin >> tmp;
		}

		ins.code = tmp;
		if(ins.code == "Halt") {
			program.push_back(ins);
			break;
		}

		if(oneOperand.count(ins.code) || twoOperands.count(ins.code)) {
			scanf(" %s", str);
			ins.operand1 = str;

			if(twoOperands.count(ins.code))
				ins.operand1.erase(ins.operand1.end()-1); //deleting the ',' to avoid varibales usage problems

			if(ins.operand1[0] != '$' && ins.code[0] != 'B' && !memory.count(ins.operand1) && !labels.count(ins.operand1)) {
				memory.insert(pair <string, int> (ins.operand1, 0));
				vars++;
				//printf("+");
			}
			if(twoOperands.count(ins.code)) {
				cin >> ins.operand2;
				if(ins.operand2[0] != '$' && ins.code[0] != 'B' && !memory.count(ins.operand2) && !labels.count(ins.operand2)) {
					memory.insert(make_pair(ins.operand2, 0));
					vars++;
					//printf("+");

				}
			}
		} else {
			cout << "invalide operation code, please entre a valide one: ";
			continue;
		}
		program.push_back(ins);
		i++;
	}

	if(program.back().code != "Halt") {
	Instruction halt;
	halt.code = "Halt";
	program.push_back(halt);
	}

//SKIP:

	while(vars--) {
		Instruction ins;
		int x;
		cin >> ins.code >> ins.operand1;
		program.push_back(ins);
		x = atoi(ins.operand1.c_str());
		memory[ins.code] = x;
	}




}



//function to print an instruction;

void printInstruction(Instruction ins) {
	char dot;
	printf("%-7s ", ins.label.c_str());
	cout << ins.code << " " << ins.operand1 << (twoOperands.count(ins.code) == 1 ? ", " : " ") << ins.operand2 ;
}

//helpful functions

int operandToInt(string str) {
	if(str[0] == '$') {
		str.erase(str.begin());
		return atoi(str.c_str());
	}
	return memory[str];
}


/********* REPERTOIRE ********/


//MOV
void MOV(Instruction ins) {
	memory[ins.operand2] = operandToInt(ins.operand1);
}

//ADD
void ADD(Instruction ins) {
	memory[ins.operand2] += operandToInt(ins.operand1);
}


//MUL
void MUL(Instruction ins) {
	memory[ins.operand2] *= operandToInt(ins.operand1);
}


//DIV
void DIV(Instruction ins) {
	memory[ins.operand2] /= operandToInt(ins.operand1);
}


//INC
void INC(Instruction ins) {
	memory[ins.operand1]++;
}


//DEC
void DEC(Instruction ins) {
	memory[ins.operand1]--;
}


//CLR
void CLR(Instruction ins) {
	memory[ins.operand1] = 0;
}


//CMP
void CMP(Instruction ins) {
	memory["CMP"] = operandToInt(ins.operand1)-operandToInt(ins.operand2);
}


//BR
void BR(Instruction ins) {
	CO = labels[ins.operand1]-1;
}


//BNE !=0
void BNE(Instruction ins) {
	if(memory["CMP"] != 0)
		CO = labels[ins.operand1]-1;
}


//BEQ =0
void BEQ(Instruction ins) {
	if(memory["CMP"] == 0/*operandToInt(program[CO-1].operand2)-operandToInt(program[CO-1].operand1) == 0*/)
		CO = labels[ins.operand1]-1;
}


//BGE >=0
void BGE(Instruction ins) {
	if(memory["CMP"] >= 0)
		CO = labels[ins.operand1]-1;
}


//BGT >0
void BGT(Instruction ins) {
	if(memory["CMP"] > 0)
		CO = labels[ins.operand1]-1;
}


//BLE <=
void BLE(Instruction ins) {
	if(memory["CMP"] <= 0)
		CO = labels[ins.operand1]-1;
}


//BLT <0
void BLT(Instruction ins) {
	if(memory["CMP"] < 0)
		CO = labels[ins.operand1]-1;
}





//printing table functions


void printFirstLine() { //                                                     *****
	printf("\u2554\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2566\u2550\u2550\u2550\u2550\n");
	printf("\u2551 %-8s \u2551", "Phase N°");

}


void printThirdLine() {
	//                                          Phase                          *****                                                 *****                                                 *****                                                                                                                               *****                                                                                                                               *****                                                ------
	printf("\u2560\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2563\n\t");

}


void printMidLine(int i, int CO, string RA, string RM, string RI, int R0) {
	//       *****       *****        *****         *****                 *****
	printf("\u2551 %-8s \u2551   %-4s \u2551   %-4s \u2551         %-11s \u2551         %-11s \u2551   %-4s \u2551\n\t", "Phase N°", "CO", "RA", "RM", "RI", "R0");

}


void printStart(string mva) {
	//                                          Phase                          *****                                                 *****                                                 *****                                                                                                                               *****                                                                                                                               *****                                                ------
	printf("\t\u2554\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2566\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2566\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2566\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2566\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2566\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2557\n\t");
	//       *****       *****        *****         *****                 *****
	printf("\u2551 %-8s \u2551   %-4s \u2551   %-4s \u2551         %-11s \u2551         %-11s \u2551   %-4s \u2551\n\t", "Phase N°", "CO", "RA", "RI", "RM", mva.c_str());
	//                                          Phase                          *****                                                 *****                                                 *****                                                                                                                               *****                                                                                                                               *****                                                ------
	//printf("\u2560\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u256C\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2563\n");

}


void printEnd() {
	//                                          Phase                          *****                                                 *****                                                 *****                                                                                                                               *****                                                                                                                               *****                                                ------
	printf("\u255A\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2569\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2569\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2569\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2569\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2569\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u255D\n");

}












