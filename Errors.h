//
// Class to manage error reporting. Note: all members are static so we can access them anywhere.
// What other choices do we have to accomplish the same thing?
//
#ifndef _ERRORS_H
#define _ERRORS_H

/**/
/*
Errors Class

NAME

	Errors - hold and display errors encountered during code execution.

DESCRIPTION

     Emulator class - Stores and displays errors. Has static members 
	 and can accessed out of the class.

AUTHOR

     Rojan Shrestha

DATE

     12/24/2017

*/
/**/

#include <string>
#include <vector>

class Errors {

public:
    
    // Initializes error reports.
    static void InitErrorReporting( );

    // Records an error message.
    static void RecordError( string &a_emsg );

    // Displays the collected error message.
    static void DisplayErrors( );
	
	//Checks if no Error recorded
	static bool Errors::isEmpty();

private:

    static vector<string> m_ErrorMsgs;
};
#endif