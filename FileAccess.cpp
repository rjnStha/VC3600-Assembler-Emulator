//
//  Implementation of file access class.
//
#include "stdafx.h"
#include "FileAccess.h"

/** /
/*
FileAccess::FileAccess( int argc, char *argv[] )

NAME

	FileAccess::FileAccess - initializer for the FileAccess class.

SYNOPSIS

FileAccess::FileAccess( int argc, char *argv[] );

	argc    --> total number of arguments pass as command line argument and 
				should not be more than two.
	*argv[] --> array of arguments with file name of the source file.

DESCRIPTION

	Class Initializer, opens the file and exits if file does not exist or could not be opened.

RETURNS

AUTHOR

	Rojan Shrestha

DATE

	12/24/2017

*/
/**/
FileAccess::FileAccess( int argc, char *argv[] )
{
    // Check that there is exactly one run time parameter.
    if( argc != 2 ) {
        cerr << "Usage: Assem <FileName>" << endl;
        exit( 1 );
    }
    // Open the file.  One might question if this is the best place to open the file.
    // One might also question whether we need a file access class.
    m_sfile.open( argv[1], ios::in );
	
    // If the open failed, report the error and terminate.
    if( ! m_sfile ) {
        cerr << "Source file could not be opened, assembler terminated."<< endl;
        exit( 1 ); 
    }
} /* FileAccess::FileAccess( int argc, char *argv[] ) */


/**/
/*
FileAccess::~FileAccess( )

NAME

	FileAccess::~FileAccess - destroyer for FileAccess class.

SYNOPSIS

	FileAccess::~FileAccess( );

DESCRIPTION

	Destroyer Function. Closes the file when the class object goes out-of-scope.

RETURNS

AUTHOR

	Rojan Shretha

DATE

	12/24/2017
*/
/**/
FileAccess::~FileAccess( )
{
    // Not that necessary in that the file will be closed when the program terminates.
    m_sfile.close( );
} /* FileAccess::~FileAccess( ) */

/**/
/*
FileAccess::GetNextLine( string &a_buff )

NAME

    FileAccess::GetNextLine - get next line from the source code.

SYNOPSIS

    bool FileAccess::GetNextLine( string &a_buff );
    a_buff    --> location of the string used to store the next line in the file.

DESCRIPTION

	Get the next line from the file. Pass by reference allows the function to store
	the value into the argument.

RETURNS

AUTHOR

	Rojan Shretha

DATE

	12/24/2017

* /
/**/
// Get the next line from the file.
bool FileAccess::GetNextLine( string &a_buff )
{
    // If there is no more data, return false.
    if( m_sfile.eof() ) return false;
    getline( m_sfile, a_buff );
    
    // Return indicating success.
    return true;
}/*bool FileAccess::GetNextLine( string &a_buff )*/



/**/
/*
FileAccess::rewind( )

NAME

    FileAccess::rewind - rewind the file for re-read.

SYNOPSIS

    void FileAccess::rewind( );

DESCRIPTION

    This function resets all the flags including the end-of-file flag and moves the file 
	access pointer to the beginning of the file for a re-read.

RETURNS

AUTHOR

    Rojan Shrestha

DATE

    12/24/2017

*/
/**/
void FileAccess::rewind( )
{
    // Clean all file flags and go back to the beginning of the file.
    m_sfile.clear();
    m_sfile.seekg( 0, ios::beg );
}/*void FileAccess::rewind( )*/
    
