//
//		Symbol table class.
//
#pragma once

/**/
/*
Symbol Table Class

NAME

	SymbolTable - this class is our symbol table.

DESCRIPTION

     SymbolTable class - holds the symbol table and displays it when function called.
     Pass I updates the symbol table and Pass II uses the table to find location of
	 the symbol.
     
AUTHOR

	Rojan Shrestha

DATE

     12/05/2017

*/
/**/

// This class is our symbol table.
class SymbolTable {

public:
    // Get rid of constructor and destructor if you don't need them.
    SymbolTable( ) {};
    ~SymbolTable( ) {};
    
    const int multiplyDefinedSymbol = 999999;

    // Add a new symbol to the symbol table.
    void AddSymbol( string &a_symbol, int a_loc );

    // Display the symbol table.
    void DisplaySymbolTable( );

    // Lookup a symbol in the symbol table.
    bool LookupSymbol( string &a_symbol, int &a_loc );

	//Return the location of given symbol
	int SymbolTable::GetSymbolLoc(string &a_symbol);

private:

    // This is the actual symbol table.  The symbol is the key to the map.
    map<string, int> m_symbolTable;

};
