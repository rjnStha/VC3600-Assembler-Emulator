#include "stdafx.h"
#include "Instruction.h"
#include "Errors.h"

/**/
/*
Instruction::ParseInstruction(string & a_buff)

NAME

    Instruction::ParseInstruction - parse the line into instruction.

SYNOPSIS

    Instruction::InstructionType Instruction::ParseInstruction(string & a_buff);
    a_buff    --> argument to be parsed, passed by reference to update it.

DESCRIPTION

    This function parses the instruction and returns the type of instruction necessary 
    to establish the location of the different labels. It also checks if the operand is 
	numeric and handles the error if the instruction consists of words more than 3.


RETURNS

    A variable of datatype 'Instruction::InstructionType' which is an enum named 'InstructionType'. 
	
AUTHOR

    Rojan Shrestha

DATE

    12/24/2017

*/
/**/
// Parse the Instruction.
Instruction::InstructionType Instruction::ParseInstruction(string &a_buff) {
	
	//converts instruction line (each characters) to lowercase
	for (int i = 0; i < a_buff.size(); i++) a_buff[i] = tolower(a_buff[i]);

	m_instruction = a_buff;

	//finds the location where the comment starts
	string::size_type startComt = m_instruction.find(';');
	//if comment found, deletes it from each line
	if (startComt != string::npos) m_instruction = m_instruction.substr(0, startComt);

	//clears the vector and resize to 0
	//allows manipulating words from current line only
	m_instructVect.clear();
	m_instructVect.resize(0);

	stringstream ss(m_instruction);
	string temp;
		
	//store each word of the line in vector
	while (ss >> temp) {                    
		m_instructVect.push_back(temp);
	}

	//initialize m_Label as empty
	m_Label = "";

	//Checks the type of instruction
	switch (m_instructVect.size())
	{
	case 0: //blank line or comment
		m_type = InstructionType(2);
		break;

	case 1: //Operation : halt and end --> Checks 1-word instruction type and updates Opcode
		if (m_instructVect[0] == "halt") m_type = InstructionType(0);
		if (m_instructVect[0] == "end") m_type = InstructionType(3);
		m_OpCode = m_instructVect[0];
		break;

	case 2: //Operation and Operand --> Checks 2-words instruction type and updates Opcode and operand
		if (m_instructVect[0] == "org") m_type = InstructionType(1);
		else m_type = InstructionType(0);
		m_OpCode = m_instructVect[0];
		m_Operand = m_instructVect[1];
		break;

	case 3: //Label, Operation and Operand --> Checks 3-words instruction type and updates Opcode, operand and label
		m_Label = m_instructVect[0];
		if (m_instructVect[1] == "dc" || m_instructVect[1] == "ds") m_type = InstructionType(1);
		else m_type = InstructionType(0);
		m_Label = m_instructVect[0];
		m_OpCode = m_instructVect[1];
		m_Operand = m_instructVect[2];
		break;

	default: //hadles errors if an instruction has more than 3 words
		string error ="Error: Incorrect Instruction, more than 3 fields";
		Errors::RecordError(error);
		break;
	}
	
	//initiliaze to set the default value as true
	m_IsNumericOperand = true;
	
	//Check if the operand is number
	try {
		m_OperandValue = stoi(m_Operand);
	}
	catch (invalid_argument&) {
		m_IsNumericOperand = false;
	}

	return m_type;
}/*Instruction::InstructionType Instruction::ParseInstruction(string &a_buff)*/

/**/
/*
Instruction::TranslateInstruction()

NAME

	Instruction::TranslateInstruction - Translates the instruction.

SYNOPSIS

	pair<string,string> Instruction::TranslateInstruction() 

DESCRIPTION

    This function partially translates instructions in the source code and generates 6 digit machine code.
	It also validates label and operand and
	handles the error if the OpCode does not match the given machine and assembly code. 
	

RETURNS
	It returns OPcode with string manipulation for convention as first element of pair and 
	the symbol as second element. returns "No Symbol" if symbol does not exist for given 
	instruction

AUTHOR

	Rojan Shrestha

DATE

	12/24/2017
	
*/
/**/
pair<string,string> Instruction::TranslateInstruction() {
	string temp1= "0",temp2;
	int pos;
	std::vector<string>::iterator it;

	//Validate the size of label and operand
	if (m_Operand.size() > 10 || m_Label.size() > 10) {
		string error = "Error: Too long(>10) label/operand: "+m_Label+"/"+m_Operand;
		Errors::RecordError(error);
	}

	//Validate label
	temp2 = m_Label;
	int size = temp2.size();
	for (int i = 0; i < size; i++) {
		//Error handling first character only letter 
		if (!(temp2[0] >= 'a' && temp2[0] <= 'z')) {
			string error = "Error:  Incorrect Label/Operand (" + temp2 + "), first char should be letter";
			cout << error << endl;
			Errors::RecordError(error);
			break;
		}

		//Error handling all character
		else if (!(temp2[i] >= 'a' && temp2[i] <= 'z') || !(temp2[i] >= '0' && temp2[i] >= '9')) {
			string error = "Error:  Incorrect Label/Operand (" + temp2 + "), letters and number only";
			Errors::RecordError(error);
			break;
		}
	}
		
	//Checks the Instruction type
	if (m_type == 0)  //Machine instruction
	{
		it = find(m_machineCodeName.begin(), m_machineCodeName.end(), m_OpCode);
		if (it == m_machineCodeName.end()) {

			//Error handling if incorrect operation code found
			temp1 = "Error, Operation not recognized: "+ m_OpCode; 
			Errors::RecordError(temp1);
		}

		else{
			//Finds the Numeric OPCode
			pos = (it - m_machineCodeName.begin() + 1);
			//string manipluation for convention. changes 1 digit numbers to 2 digit
			//using append
			if(pos<10) temp1.append(to_string(pos));
			else temp1 = to_string(pos);

			//Updates pair values for halt operation
			temp2 = m_Operand;
			if (m_OpCode == "halt") {
				temp1 = temp1 + "0000";
				temp2 = "No Symbol"; //no symbol to pass
			}
		}
	}
	else if (m_type == 1)	//Assembly instruction 
	{
		it = find(m_assemblyCodeName.begin(), m_assemblyCodeName.end(), m_OpCode);
		if (it == m_assemblyCodeName.end()) {
			//Error handling if incorrect operation code found
			temp1 = "Error, Operation not recognized: " + m_OpCode; 
			Errors::RecordError(temp1);
			}
		else {
			//updates pair values for operation dc
			if (m_OpCode == "dc") {
				temp1 = m_Operand;
				//set the istruction size to 6 by adding 0s
				while (temp1.size() != 6) temp1 = "0" + temp1;
			}
			else temp1 = "";
			temp2 = "No Symbol"; //no symbol to pass

		}
	}
	
	return  pair<string, string>(temp1, temp2);
}/*pair<string,string> Instruction::TranslateInstruction() */


/**/
/*
Instruction::LocationNextInstruction(int a_loc)

NAME

    Instruction::LocationNextInstruction - get location for next line of code.

SYNOPSIS

    int Instruction::LocationNextInstruction(int a_loc);
    a_loc    --> location for the current instruction.

DESCRIPTION

    Computes the location for the next line of machine code based on current 
	instruction position and handling the operandvalue to update the location

RETURNS

    Location for next instruction 

AUTHOR

    Rojan Shrestha

DATE

    12/24/2017

*/
/**/
int Instruction::LocationNextInstruction(int a_loc) {
	if (m_OpCode == "org" || m_OpCode == "ds") return a_loc + m_OperandValue;
	return ++a_loc;
}/*int Instruction::LocationNextInstruction(int a_loc)*/

