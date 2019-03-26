//
//		Assembler class.  This is a container for all the components
//		that make up the assembler.
//
#pragma once 

/**/
/*
Assembler Class

NAME

	Assembler -  reads and translates the assembly code into VC3600 machine code.

DESCRIPTION

	This is a container for all the components that make up the assembler.

AUTHOR

	Rojan Shrestha

DATE

	12/24/2017

*/
/**/
#include "SymTab.h"
#include "Instruction.h"
#include "FileAccess.h"
#include "Emulator.h"


class Assembler {

public:
    Assembler( int argc, char *argv[] );
    //~Assembler( );

    // Pass I - establish the locations of the symbols
    void PassI( );

    // Pass II - generate a translation
    void PassII( );

    // Display the symbols in the symbol table.
    void DisplaySymbolTable() { m_symtab.DisplaySymbolTable(); }
    
    // Run emulator on the translation.
    void RunEmulator();

private:

    FileAccess m_facc;	    // File Access object
    SymbolTable m_symtab; // Symbol table object
    Instruction m_inst;	    // Instruction object
    emulator m_emul;        // Emulator object
	
	// Vector to store the machine code
	vector<pair<int, string>> m_machineCode;
};

