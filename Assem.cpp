/**/
/*
Assem

NAME

	Assem - main file that runs the program.
DESCRIPTION

	Assem - calls all the method functions that runs the program.
	
AUTHOR

	Rojan Shrestha

DATE

	12/24/2017
	
*/
/**/

#include "stdafx.h"     // This must be present if you use precompiled headers which you will use.
#include <stdio.h>

#include "Assembler.h"

int main( int argc, char *argv[] )
{
	
    Assembler assem( argc, argv );
	
    // Establish the location of the labels:
    assem.PassI( );
	
    // Display the symbol table.
    assem.DisplaySymbolTable();
	
    // Output the symbol table and the translation.
    assem.PassII( );
    
    // Run the emulator on the VC3600 program that was generated in Pass II.
    assem.RunEmulator();
   
    // Terminate indicating all is well.  If there is an unrecoverable error, the 
    // program will terminate at the point that it occurred with an exit(1) call.
	system("pause");
    return 0;
}
