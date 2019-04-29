//
// Created by Ali A. Kooshesh on 1/30/19.
//

#include <iostream>
#include "Token.hpp"

Token::Token(): _stringS{""}, _name{""}, _eof{false}, _eol{false}, _symbol{'\0'}, _stringSymbol{""}, _isWholeNumber{false} {}

void Token::print() const {
    for (int i = 0; i < indent(); i++) {std::cout << " ";}
    if( eol() ) std::cout << "EOL\n" ;
    else if( eof() )                    std::cout << "EOF" ;
    else if( isOpenParen() )  std::cout << "(" ;
    else if( isCloseParen() )  std::cout << ")" ;
    else if( isAssignmentOperator() )  std::cout << " = " ;
//    else if( isSemiColon() )  std::cout << ";" ;
    else if( isMultiplicationOperator() )  std::cout << " * " ;
    else if( isAdditionOperator() )  std::cout << " + " ;
    else if( isSubtractionOperator() )  std::cout << " - " ;
    else if( isModuloOperator() )  std::cout << " % " ;
    else if( isDivisionOperator() )  std::cout << " / " ;
    else if( isGreaterThanOperator() )  std::cout << " > " ;
    else if( isLessThanOperator() )  std::cout << " < " ;
    else if( isGreaterThanOrEqualToOperator() )  std::cout << " >= " ;
    else if( isLessThanOrEqualToOperator() )  std::cout << " <= " ;
    else if( isEqualToOperator() )  std::cout << " == " ;
    else if( isNotEqualToOperator() )  std::cout << " != " ;
    else if( isStringS() ) std::cout << getStringS();
    else if( isForLoop() ) std::cout << "for";
    else if( isPrintStmt() ) std::cout << "print";
    else if( isName() )  std::cout << getName();
    else if( isWholeNumber() ) std::cout << getWholeNumber();
    else if( isHashtag() ) std::cout << " # " ;
    else if( isComma() ) std::cout << ", " ;
    else if( isDoubleQuotationMark() ) std::cout << '"';
    else if( isSingleQuotationMark() ) std::cout << '\'';
    else std::cout << "Uninitialized token.\n";
}
