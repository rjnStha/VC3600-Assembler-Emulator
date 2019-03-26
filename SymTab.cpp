//
//		Implementation of the symbol table class.
//
#include "stdafx.h"
#include "SymTab.h"

/*
NAME

    AddSymbol - adds a new symbol to the symbol table.

SYNOPSIS

    void AddSymbol( char *a_symbol, int a_loc );
	a_symbol    --> the symbol being added to be the table.
	a_loc       --> the location of the symbol.

DESCRIPTION

    Stores symbol of a_symbol and its location in a_loc in the symbol table.

RETURNS

AUTHOR

	Rojan Shrestha

DATE

	12/24/2017

*/
void 
SymbolTable::AddSymbol( string &a_symbol, int a_loc )
{
    // If the symbol is already in the symbol table, record it as multiply defined.
    map<string, int>::iterator st;
    st = m_symbolTable.find( a_symbol );
    if( st != m_symbolTable.end() ) {
        st->second = multiplyDefinedSymbol;
        return;
    }
    // Record the location in the symbol table.
	 m_symbolTable[a_symbol] = a_loc;
}/*SymbolTable::AddSymbol( string &a_symbol, int a_loc*/


/**/
/*
SymbolTable::DisplaySymbolTable()

NAME

    SymbolTable::DisplaySymbolTable - prints symbol table.

SYNOPSIS

    void SymbolTable::DisplaySymbolTable();

DESCRIPTION

    This function will prints all the symbol table in specific format.

RETURNS

AUTHOR

	Rojan Shrestha

DATE

    12/05/2017

*/
/**/
void SymbolTable::DisplaySymbolTable() {
	int indx = 0;
	cout << "Symbol#"<< "\t " << "Symbol"<<"\t " <<"Location" << endl;
	for (map<string, int>::iterator it = m_symbolTable.begin(); it != m_symbolTable.end(); ++it) {
		cout <<"   " << indx++ << "\t  " << it->first << "\t  " << it->second << endl;
	}
}/*void SymbolTable::DisplaySymbolTable()*/

/**/
/*
SymbolTable::LookupSymbol(const string & a_symbol, int & a_loc)

NAME

	SymbolTable::LookupSymbol - lookup a symbol in the table.

SYNOPSIS

    bool SymbolTable::LookupSymbol(const string & a_symbol, int & a_loc);
    a_symbol    --> the symbol to be searched for.
    a_loc       --> if the symbol is found, the location is stored in a_loc. if not, a_loc is unchanged.

DESCRIPTION

    This function looks up a symbol in the symbol table and if found, stores the location of the symbol.

RETURNS

    'true' if symbol found else 'false'.

AUTHOR

    Rojan Shrestha

DATE

    12/24/2017

*/
bool SymbolTable::LookupSymbol(string &a_symbol, int &a_loc) {
	map<string, int>::iterator it = m_symbolTable.find(a_symbol);
	if (it == m_symbolTable.end()) return false;
	a_loc = it->second;
	return true;
}/*bool SymbolTable::LookupSymbol(string &a_symbol, int &a_loc)*/

/**/
/*

int SymbolTable::GetSymbolLoc(string &a_symbol) 

NAME

	SymbolTable::GetSymbolLoc - gets the location of given symbol.

SYNOPSIS
	int SymbolTable::GetSymbolLoc(string &a_symbol) 
    a_symbol    --> the symbol whose location is to be searched for
    
DESCRIPTION

    This function looksup a symbol in the symbol table and if found returns its location.

RETURNS
	
	the location of the given symbol in the symbol table

AUTHOR

    Rojan Shrestha

DATE

    12/24/2017

*/
/**/
int SymbolTable::GetSymbolLoc(string &a_symbol) {
	map<string, int>::iterator it;
	it = m_symbolTable.find(a_symbol);
	return it->second;
}/*int SymbolTable::GetSymbolLoc(string &a_symbol)*/