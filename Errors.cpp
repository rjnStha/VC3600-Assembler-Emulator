#include "stdafx.h"
#include "Errors.h"

vector<string> Errors::m_ErrorMsgs;

/**/
/*
Errors::InitErrorReporting()
NAME

    Errors::InitErrorReporting - initializer for the class.

SYNOPSIS

    void Errors::InitErrorReporting();

DESCRIPTION

    Initialize the class for error reporting by clearing the vector of errors.

RETURNS

AUTHOR

    Rojan Shrestha

DATE

    12/24/2017

*/
/**/
void Errors::InitErrorReporting() {
	m_ErrorMsgs.erase(m_ErrorMsgs.begin(), m_ErrorMsgs.end());
}/* void Errors::InitErrorReporting() */

 /**/
 /*
 
void Errors::RecordError(const string &a_emsg)
 
NAME
 
	Errors::RecordError(const string &a_emsg) - Records the error as string
 
SYNOPSIS
 
	void Errors::RecordError(const string &a_emsg)
	a_emsg		-->			Contains the error message
 
DESCRIPTION
 
	This function records the given error passed through string and stores it in the error vector.
 
RETURNS
 
	VOID
 
AUTHOR

	Rojan Shrestha

DATE

	12/24/2017

 */
 /**/
void Errors::RecordError(string &a_emsg) {
	m_ErrorMsgs.push_back(a_emsg);
}/* void Errors::RecordError(const string &a_emsg)*/

 /**/
 /*
void Errors::DisplayErrors()

NAME

	void Errors::DisplayErrors() - display recorded errors

SYNOPSIS

	void Errors::DisplayErrors()

DESCRIPTION

	This function prints out all of the errors after translating the code

RETURNS

	VOID

AUTHOR

	Rojan Shrestha

DATE

	12/24/2017

 */
 /**/
void Errors::DisplayErrors() {
	for (int i = 0; i < m_ErrorMsgs.size(); ++i) {
		cout << m_ErrorMsgs[i] << endl;
	}
}/* void Errors::DisplayErrors()*/

 /**/
 /*
bool Errors::isEmpty()

NAME

	Errors::isEmpty() - Checks if there are any errors in the record

SYNOPSIS

	bool Errors::isEmpty()

DESCRIPTION

	This function checks if there are any errors during the translation by checking the vector holding error messages

RETURNS

	Returns true if the error message vector is empty, false otherwise.

AUTHOR

	Rojan Shrestha

DATE

	12/24/2017

*/
/**/
bool Errors::isEmpty() {
	return m_ErrorMsgs.empty();
} /* bool Errors::isEmpty()*/
