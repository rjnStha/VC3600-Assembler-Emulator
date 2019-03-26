//
//      Implementation of the Assembler class.
//
#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"
#include "Emulator.h"


/**/
/*
Assembler::Assembler( int argc, char *argv[] )

NAME

	Assembler::Assembler - constructor for the Assembler class.

SYNOPSIS

	Assembler::Assembler( int argc, char *argv[] );
	argc              --> total number of arguments received in the command line.
	*argv[]           --> a pointer to the array of arguments passed through the command line.

DESCRIPTION

	Constructor for the assembler. Note: we are passing argc and argv to the file access constructor.

RETURNS

AUTHOR

	Rojan Shrestha

DATE

12/24/2017

*/
/**/
Assembler::Assembler( int argc, char *argv[] )
: m_facc( argc, argv )
{
    // Nothing else to do here at this point.
}/* Assembler::Assembler( int argc, char *argv[] ) */


/**/
/*
Assembler::PassI()

NAME

	Assembler::PassI - first pass through the source code.

SYNOPSIS

Assembler::PassI();

DESCRIPTION

	 Pass I establishes the location of the labels and constructs a symbol table.

RETURNS

AUTHOR

	Rojan Shrestha

DATE

	12/24/2017

*/
/**/
void Assembler::PassI( ) 
{
    int loc = 0;        // Tracks the location of the instructions to be generated.

    // Successively process each line of source code.
    for( ; ; ) {

        // Read the next line from the source file.
        string buff; 
        if( ! m_facc.GetNextLine( buff ) ) {

            // If there are no more lines, we are missing an end statement.
            // We will let this error be reported by Pass II.
            return;
        }
				
		// Parse the line and get the instruction type.
        Instruction::InstructionType st =  m_inst.ParseInstruction( buff );
		
        // If this is an end statement, there is nothing left to do in pass I.
        // Pass II will determine if the end is the last statement.
		if (st == Instruction::ST_End) return;
		
        // Labels can only be on machine language and assembler language
        // instructions.  So, skip other instruction types.
        if( st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr ) 
        {
        	continue;
		}

        // If the instruction has a label, record it and its location in the
        // symbol table.
        if( m_inst.isLabel( )) {

			m_symtab.AddSymbol( m_inst.GetLabel( ), loc);
        }

		// Compute the location of the next instruction.
        loc = m_inst.LocationNextInstruction( loc );
		
	}
} /* void Assembler::PassI() */


 /**/
 /*
 Assembler::PassII()

 NAME

	Assembler::PassII - second pass through the source code.

 SYNOPSIS

	void Assembler::PassII();

DESCRIPTION

	Pass II parses the instruction to get label, operation code an operand using the symbol table updated
	by Pass I. It calls TranlateInstruction function to get translate the source code into machine code for
	the VC-3600 computer. It also records errors encountered during translation and prints them at the end 
	of the program. It then stores the translated instruction in a vector of pairs for future purpose and 
	displays the orignal assembler instruction and its machine language equivalent 

RETURNS

AUTHOR

	Rojan Shrestha

DATE

	12/24/2017

  */
 /**/
void Assembler::PassII()
{
	m_facc.rewind(); // Resets the flags for the open file so it can be read again from the top
	
	int loc = 0;        // Tracks the location of the instructions to be generated.
	bool endStatus = false; //checks if end statement found
	Errors::InitErrorReporting();	//Function call to initiliaze error reporting
	m_machineCode.clear(); 		//Clear the vector
	string error;	//variable to store errors
					
	// Print the header for translation table output 
	cout <<"Location	Contents	Original Statement" << endl;

	// Successively process each line of source code.
	for (; ; ) {
		string buff;

		//Checks Error if there are instructions after end statement
		//prints error if end status true
		if (endStatus == true){

			//Checks for other statments after end
			if(m_facc.GetNextLine(buff) == true) {
				error = "Error: Another (blank)line / Instruction after End Statement";
				Errors::RecordError(error);
			}

			//Prints the error
			if (!Errors::isEmpty()) Errors::DisplayErrors();
			break;
		}

		// Read the next line from the source file.
		if (!m_facc.GetNextLine(buff)) {
			
			//ERROR :  no more lines and missing end statement
			error = "End Statement Missing";
			Errors::RecordError(error);
			break;
		}

		// Parse the line and get the instruction type.
		Instruction::InstructionType st = m_inst.ParseInstruction(buff);
		
		//Updates the end status if end statement found
		if (st == Instruction::ST_End) 
		{ 
			endStatus = true;
			cout <<"			"<<buff << endl;
			continue; 
		}


		// Labels can only be on machine language and assembler language
		// instructions.  So, skip other instruction types.
		if (st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr)
		{
			if (st == Instruction::ST_Comment) cout <<"				" <<buff << endl;
			continue;
		}
		
		//function to get mmachine instruction contents
		pair<string,string> contentValue = m_inst.TranslateInstruction();

		//Record error if incorrect operation code found
		//after calling function Instruction::NumOpCode()
		if ((contentValue.first).find("Error") != string::npos) continue; //skip the instruction 
				
		//checks for symbol and if found gets its location
		else if ((contentValue.second).find("No Symbol") == string::npos) {
			//function call to get location of label 
			string temp = to_string(m_symtab.GetSymbolLoc(contentValue.second));

			//set the istruction size to 6 by adding 0s
			while (temp.size() != 4) temp = "0" + temp;
			(contentValue.first).append(temp);
		}	
		//prints location-content-buff
		cout << loc << "		" << contentValue.first << "		" << buff << endl;


		//insert 6 digit instruction into vector for future use
		m_machineCode.push_back(make_pair(loc, contentValue.first));
		
		// Compute the location of the next instruction.
		loc = m_inst.LocationNextInstruction(loc);

	}
} /*void Assembler::PassII()*/


/**/
/*
Assembler::RunEmulator()

NAME
    Assembler::RunEmulator - run the emulator on the translated code.

SYNOPSIS

	void Assembler::RunEmulator();

DESCRIPTION

	Access the translated code from Pass II stored in vector and runs the emulator.	Also checks 
	for error when running the emulator
	
	If errors have been encountered, emulation is halted. 
    If not, the function loads all the translated instruction into the emulator's memory and then runs the emulator. 
    This function also  detects errors encountered during emulation and reports them after.

RETURNS

AUTHOR

	Rojan Shrestha

DATE

	12/05/2017

*/
/**/
void Assembler::RunEmulator() {
	
	
	for (vector<pair<int, string>>::iterator it = m_machineCode.begin(); it != m_machineCode.end(); ++it) {
		int temp;
		//Checks for error if the machine Code is incorrect and cannot 
		//be converted to int from string 
		try {
			temp = stoi(it->second);
		}
		catch (invalid_argument&) {
			//ignore the faulty machine Code
			continue;
		}

		bool insertion_check = m_emul.insertMemory(it->first, temp);
		if (insertion_check == false) {
			string error = "Error inserting the command " + to_string(it->first) + " " + it->second + " into the emulator memory";
			Errors::RecordError(error);
		}
	}

	// Run program and report error if program run failed.
	if (!m_emul.runProgram()) {
		string error = "Error: Emulator error runnning";
		Errors::RecordError(error);
	}

	// Display any errors after running program.
	if (!Errors::isEmpty()) Errors::DisplayErrors();

}/*void Assembler::RunEmulator() {*/