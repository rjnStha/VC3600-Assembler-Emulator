//
//      Implementation of the Emulator class.
//
#include "stdafx.h"
#include "Emulator.h"
//#include "Errors.h"

/**/
/*
emulator::insertMemory(int a_location, int a_contents)

NAME

	emulator::insertMemory - insert 6 digit instruction into emulator memory.

SYNOPSIS

	bool emulator::insertMemory(int a_location, int a_contents);
	a_location     --> location of the instruction, should be less than 10,000.
	a_contents     --> 6 digit number, machine instruction

DESCRIPTION

	Insert 6 digit machine code instruction and its euivalent location into the memory of emulator.
	Also sets the location of the first instruction for emulation.

RETURNS

	true if insertion success else false

AUTHOR

	Rojan Shrestha

DATE

	12/24/2017

*/
/**/

// Records instructions and data into VC3600 memory.
bool emulator::insertMemory(int a_location, int a_contents)
{
	//checks if location is within bound and store the contents to the location
	if (a_location < MEMSZ && a_location >= 0) m_memory[a_location] = a_contents;

	else {
		//Error handling location out of bound
		string error = "Error: Location out of bound";
		return false;
	}


	return true;
}/*bool emulator::insertMemory(int a_location, int a_contents)*/

 /**/
 /*
 bool Emulator::runProgram()

 NAME

	 Emulator::runProgram() - Runs the emulator

 SYNOPSIS

	bool Emulator::runProgram()

 DESCRIPTION

	This function runs the emulator for the assembler. It carries all the machine
	instruction using the 6 digit machine code. 

 RETURNS

	 Returns true if the program succeeds running, false otehrwise.

 AUTHOR

	Rojan Shrestha

 DATE

	12/24/2015
	1
 */
bool emulator::runProgram() {
	
	int opCode = 0; //store the op Code from the 6 digit instruction
	int userInput = 0;
	int location = 0;
	
	for (int indx = 0; indx < MEMSZ; ++indx) {
		if (m_memory[indx] != 0) {

			//extracting the opcode from the 6 digit instruction
			opCode = m_memory[indx] / 10000;
			//extracting the location from the 6 digit instruction
			location = m_memory[indx] % 10000;
			
			switch (opCode) {
			case 1:
				// Addition
				//the content of accumulator and memory location 
				accumulator += m_memory[location];
				break;
			case 2:
				// Substraction
				//the contents of accumulator and memory location
				accumulator -= m_memory[location];
				break;
			case 3:
				// Multiplication
				//the contents of accumulator and memory location 
				accumulator *= m_memory[location];
				break;
			case 4:
				// Division
				//the contents of accumulator and memory location 
				accumulator = accumulator / m_memory[location];
				break;
			case 5:
				// Loads the content of the location into the accumulator
				accumulator = m_memory[location];
				break;
			case 6:
				// The contents of accumulator is stored in the location 
				m_memory[location] = accumulator;
				break;
			case 7:
				// A line is read and its first 6 digits are placed in the specified location
				cout << "?";
				cin >> userInput;
				userInput = userInput % 1000000;
				m_memory[location] = userInput;
				break;
			case 8:
				// Prints the Contents of the location 
				cout << m_memory[location] << endl;
				break;
			case 9:
				// sets the index to the location for next instruction
				indx = location;
				break;
			case 10:
				// sets index as location if the content of accumulator < 0
				if (accumulator < 0) indx = location - 1;
				break;
			case 11:
				// sets index as location if the content of accumulator = 0
				if (accumulator == 0) indx = location - 1;
				break;
			case 12:
				// sets index as location if the content of accumulator > 0
				if (accumulator > 0) indx = location - 1;
				break;
			case 13:
				// terminates the execution
				indx = 10000;
				break;
			default:
				//if the opCode is out of bound
				return false;
			}
		}
	}
	return true;
}/* bool Emulator::runProgram()*/