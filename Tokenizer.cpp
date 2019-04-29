//
// Created by Ali A. Kooshesh on 1/30/19.
//

#include <iostream>
#include <string>
#include "Tokenizer.hpp"

std::string Tokenizer::readRelation() {
    std::string relation;
    char c;
    inStream.get(c);
    relation += c;
    inStream.get(c);
    relation += c;
    return relation;
}

std::string Tokenizer::readName() {
    // This function is called when it is known that
    // the first character in input is an alphabetic character.
    // The function reads and returns all characters of the name.

    std::string name;
    char c;
    while( inStream.get(c) && isalnum(c) ) {
        name += c;
    }
    if(inStream.good())  // In the loop, we have read one char too many.
        inStream.putback(c);
    return name;
}

std::string Tokenizer::readQuote() {
    // This function is called when it is known that
    // the first character in input is an alphabetic character.
    // The function reads and returns all characters of the name.

    std::string quote;
    char c;
    inStream.get(c);
    quote += c;
    while( inStream.get(c) && c != '"' ) {
        quote += c;
    }
    if ( c != '"' ) {
        std::cout << "Missing Quotation Mark in input. " << std::endl;
        exit(1);
    }
    quote += c;
    return quote;
}

int Tokenizer::readInteger() {
    // This function is called when it is known that
    // the first character in input is a digit.
    // The function reads and returns all remaining digits.

    int intValue = 0;
    char c;
    while( inStream.get(c) && isdigit(c) ) {
        intValue = intValue * 10 + c - '0';
    }
    if(inStream.good())  // In the loop, we have read one char too many.
        inStream.putback(c);
    return intValue;
}

Tokenizer::Tokenizer(std::ifstream &stream): ungottenToken{false}, inStream{stream}, lastToken{} {}

Token Tokenizer::getToken() {

    if(ungottenToken) {
        ungottenToken = false;
        return lastToken;
    }

    char c;
    /*
    while( inStream.get(c) && isspace(c) && c != '\n' )  // Skip spaces but not new-line chars.
        ;
    */

    std::string tab;
    int indent = 0;

    while (inStream.get(c)) {
        inStream.putback(c);

        while (inStream.get(c) && isspace(c) && c != '\n')  // Skip spaces but not new-line chars.
        {
            tab += c;
            if (tab == " ") {
                indent++;
                tab = "";
            }
        }

	_indents.push(indent);
        // if the 'c' you just got is a comment sign
        if (c == '#') {
            std::cout << "we found a comment\n";
            while (inStream.get(c) && c != '\n')
                ;
            //inStream.get(c);
        }
        else
            break;
    }

    if(inStream.bad()) {
        std::cout << "Error while reading the input stream in Tokenizer.\n";
        exit(1);
    }

    //    std::cout << "c = " << c << std::endl;

    Token token;
    token.indent(indent);
    if( inStream.eof()) {
        token.eof() = true;
    } else if( isdigit(c) ) { // a integer?
        // put the digit back into the input stream so
        // we read the entire number in a function
        inStream.putback(c);
        token.setWholeNumber( readInteger() );

    } else if( c == '=' || c == '>' || c == '<' || c == '!' ) {
        char s = c;
        inStream.get(c);
        if ( c == '=' ) {
            // Set Relational Operator
            inStream.putback(c);
            inStream.putback(s);
            token.setRelation( readRelation() );
        } else {
            inStream.putback(c);
            token.symbol(s);
        }
    } else if( c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
        token.symbol(c);
    else if( c == ';' )
        token.symbol(c);
    else if( c == '(' || c == ')' || c == '{' || c == '}')
        token.symbol(c);
    else if( c == '"' ) {
	inStream.putback(c);
	token.setName( readQuote() );
    } else if(isalpha(c)) {  // an identifier?
        // put c back into the stream so we can read the entire name in a function.
        inStream.putback(c);
	token.isStringS() = false;
        token.setName( readName() );
    } else if( c == ',' ) {
	token.symbol(c);
    } else if(c == '\n') {
        //token.symbol(c);
        token.eol() = true;

        while(inStream.get(c)){
            if (c != '\n'){
                inStream.putback(c);
                break;
            }

        }
    } else {
        std::cout << "Unknown character in input. ->" << c << "<-" << std::endl;
        exit(1);
    }
    _tokens.push_back(token);
    return lastToken = token;
}

void Tokenizer::ungetToken() {
    ungottenToken = true;
}

void Tokenizer::printProcessedTokens() {
    for(auto iter = _tokens.begin(); iter != _tokens.end(); ++iter) {
        iter->print();
        std::cout << std::endl;
    }
}

int Tokenizer::getIndent() {
    int _indent = _indents.top();
    _indents.pop();
    return _indent;
}
