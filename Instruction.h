//
// Class to parse and provide information about instructions.  Note: you will be adding more functionality.
//
#pragma once
/**/
/*
Instruction Class

NAME

     Instruction - deal with individual instructions from the source code.

DESCRIPTION

     Instruction class - parse the instructions and important in forming symbol table 
	 and tranlating instruction to machine code.

AUTHOR

     Rojan Shrestha

DATE

     12/24/2017

*/
/**/

// The elements of an instruction.
class Instruction {

public:

	Instruction() { };
	~Instruction() { };

	// Codes to indicate the type of instruction we are processing.  Why is this inside the
	// class?
	enum InstructionType {
		ST_MachineLanguage, // A machine language instruction.
		ST_AssemblerInstr,  // Assembler Language instruction. {"org", "dc", "ds", "end" }
		ST_Comment,         // Comment or blank line
		ST_End,             // end instruction.

	};
	// Parse the Instruction.
	InstructionType ParseInstruction(string &a_buff);

	// Compute the location of the next instruction.
	int LocationNextInstruction(int a_loc);

	// computes and returns OPcode along with the symbol 
	pair<string, string> TranslateInstruction();

	// To access the label
	inline string &GetLabel() {

		return m_Label;
	};


	//To determine if a label is blank.
	inline bool isLabel() {

		return !m_Label.empty();
	};


private:


	// The elemements of a instruction
	string m_Label;         // The label.
	string m_OpCode;       // The symbolic op code.
	string m_Operand;      // The operand.


	string m_instruction;    // The original instruction.

	// Derived values.
	int m_NumOpCode;     // The numerical value of the op code.
	InstructionType m_type; // The type of instruction.

	bool m_IsNumericOperand;// == true if the operand is numeric.
	int m_OperandValue;   // The value of the operand if it is numeric.

	//vector to store each word of the instruction line
	vector<string> m_instructVect;

	//vector to store each machine code and assembly code
	vector<string> m_machineCodeName = {"add", "sub", "mult", 
		"div","load","store","read","write","b","bm","bz","bp","halt" };
	vector<string> m_assemblyCodeName = { "org", "dc", "ds", "end" };

};