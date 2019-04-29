#ifndef EXPRINTER_TOKEN_HPP
#define EXPRINTER_TOKEN_HPP
#include<string>

class Token {

public:
    Token();

    bool &eof()  { return _eof; }
    bool &eol()  { return _eol; }

    bool eof() const { return _eof; }
    bool eol() const  { return _eol; }

    bool isOpenParen() const  { return _symbol == '('; }
    bool isCloseParen() const { return _symbol == ')'; }
    bool isOpenBrace() const  { return _symbol == '{'; }
    bool isCloseBrace() const { return _symbol == '}'; }

    void symbol(char c) { _symbol = c; }
    char symbol() { return _symbol; }

    bool isSemiColon() const { return _symbol == ';'; }
    bool isAssignmentOperator() const              { return _symbol == '='; }
    bool isMultiplicationOperator() const { return _symbol == '*'; }
    bool isAdditionOperator() const       { return _symbol == '+'; }
    bool isSubtractionOperator() const    { return _symbol == '-'; }
    bool isModuloOperator() const         { return _symbol == '%'; }
    bool isDivisionOperator() const       { return _symbol == '/'; }
    bool isArithmeticOperator() const {
        return isMultiplicationOperator() ||
               isAdditionOperator() ||
               isSubtractionOperator() ||
               isModuloOperator() ||
               isDivisionOperator();
    }
    bool isGreaterThanOperator() const           { return _symbol == '>'; }
    bool isLessThanOperator() const             { return _symbol == '<'; }
    bool isGreaterThanOrEqualToOperator() const  { return _relation == ">="; }
    bool isLessThanOrEqualToOperator() const     { return _relation == "<="; }
    bool isEqualToOperator() const          { return _relation == "=="; }
    bool isNotEqualToOperator() const          { return _relation == "!="; }
    bool isRelationalOperator() const {
        return isGreaterThanOperator() ||
        isLessThanOperator() ||
        isGreaterThanOrEqualToOperator() ||
        isLessThanOrEqualToOperator() ||
        isEqualToOperator() ||
        isNotEqualToOperator();
    }
    bool isName() const                   { return _name.length() > 0; }
    bool isRelation() const		  { return _relation.length() > 0; }
    void setRelation(std::string r) { _relation = r; }
    std::string getName() const                  { return _name; }
    std::string getRelation() const		 { return _relation; }
    void setName(std::string n) { _name = n; }

    bool &isWholeNumber() { return _isWholeNumber; }
    bool isWholeNumber() const { return _isWholeNumber; }
    int getWholeNumber() const { return _wholeNumber; }
    void setWholeNumber(int n) {
        _wholeNumber = n;
        isWholeNumber() = true;
    }
    
    bool isForLoop() const { return _name == "for"; }
    bool isPrintStmt() const { return _name == "print"; }
    bool isKeyword() const {
        return isForLoop() ||
                isPrintStmt();
    }
    bool isHashtag() const { return _symbol == '#'; }

    void print() const;

    bool isDoubleQuotationMark() const { return _symbol == '"';}
    bool isSingleQuotationMark() const { return _symbol == '\''; }
    bool &isStringS() { return _isStringS; }
    bool isStringS() const { return _isStringS; }
    std::string getStringS() const { return _stringS; }
    void setStringS(std::string n) {
        _stringS = n;
        isStringS() = true;
    }
    bool isComma() const { return _symbol == ','; }
    bool isNewLine() const { return _symbol == '\n'; }
    void indent(int i) { _indent = i; }
    int indent() const { return _indent; }

private:
    std::string _stringS;
    std::string _stringSymbol;
    std::string _name;
    std::string _relation;
    bool _eof, _eol;
    bool _isWholeNumber;
    bool _isStringS;
    char _symbol;
    int _wholeNumber;
    int _indent;
};

#endif //EXPRINTER_TOKEN_HPP
