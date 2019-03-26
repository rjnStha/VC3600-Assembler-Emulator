//
//		File access to source file.
//
#ifndef _FILEACCESS_H  // This is the way that multiple inclusions are defended against often used in UNIX
#define _FILEACCESS_H // We use pramas in Visual Studio.  See other include files

/**/
/*
FileAccess Class

NAME

	FileAccess - provide tools to access file.

DESCRIPTION

	FileAccess class - opens and reads the source file. File name is provided as a command line argument.

AUTHOR

	Rojan Shrestha

DATE

	12/24/2017

*/
/**/


#include <fstream>
#include <stdlib.h>
#include <string>

class FileAccess {

public:

    // Opens the file.
    FileAccess( int argc, char *argv[] );

    // Closes the file.
    ~FileAccess( );

    // Get the next line from the source file.
    bool GetNextLine( string &a_buff );

    // Put the file pointer back to the beginning of the file.
    void rewind( );

private:

    ifstream m_sfile;		// Source file object.
};
#endif

