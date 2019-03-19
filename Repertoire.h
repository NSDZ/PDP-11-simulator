/** header file **/

#include <bits/stdc++.h>
using namespace std;



// creating a "Instruction" data type

typedef struct Instruction  {
	string code, operand1, operand2, label;
};


//instruction types

extern set <string> twoOperands, oneOperand;


//program memory

extern vector <Instruction> program;


//Registres & variables memory;

extern map <string, int> memory, labels;

extern int CO;



//function to read input

void scanProgram();


//function to print instruction

void printInstruction(Instruction inst);



//helpful functions

int operandToInt(string str);



/********* REPERTOIRE ********/


//MOV
void MOV(Instruction ins);

//ADD
void ADD(Instruction ins);


//MUL
void MUL(Instruction ins);


//DIV
void DIV(Instruction ins);


//INC
void INC(Instruction ins);


//DEC
void DEC(Instruction ins);


//CLR
void CLR(Instruction ins);


//CMP
void CMP(Instruction ins);


//BR
void BR(Instruction ins);


//BNE !=0
void BNE(Instruction ins);


//BEQ =0
void BEQ(Instruction ins);


//BGE >=0
void BGE(Instruction ins);


//BGT >0
void BGT(Instruction ins);


//BLE <=
void BLE(Instruction ins);


//BLT <0
void BLT(Instruction ins);



//printing table functions


void printFirstLine();

void printThirdLine();

void printMidLine();

void printStart(string mva);

void printEnd();










