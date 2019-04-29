
/*  The majority of the work is done by the class 'convert'.
    This class builds an expression tree using the input infix
    expression.  A post-order traversal of the expression tree 'dumps'
    it into an array in postfix form.  The iterator copies the token
    from this array to user's arrays.

*/

#include<vector>
#include<iostream>

#include "Token.hpp"
#include "Parser.hpp"
#include "Statements.hpp"

// Parser functions

void Parser::die(std::string where, std::string message, Token &token) {
    std::cout << where << " " << message << std::endl;
    token.print();
    std::cout << std::endl;
    std::cout << "\nThe following is a list of tokens that have been identified up to this point.\n";
    tokenizer.printProcessedTokens();
    exit(1);
}

Statements *Parser::statements() {
    Statements *stmts = new Statements();
    Token tok = tokenizer.getToken();
    while (tok.isName()) {
        if(tok.isKeyword()){
            //For stmt and print stmt
            if(tok.isPrintStmt()){
                tokenizer.ungetToken();
                //std::cout << "Parsing a print statement\n";
                PrintStatement *printstmt = printStatement();
                stmts->addStatement(printstmt);
                tok = tokenizer.getToken();
            }
            if(tok.isForLoop()){
                // Do For Loops
                tokenizer.ungetToken();
                ForStatement *forstmt = forStatement();
                stmts->addStatement(forstmt);
                tok = tokenizer.getToken();
            }
        }
        else {
            tokenizer.ungetToken();
            AssignmentStatement *assignStmt = assignStatement();
            stmts->addStatement(assignStmt);
            tok = tokenizer.getToken();
        }
        // Add a get token here
        //tok = tokenizer.getToken();
    }


    tokenizer.ungetToken();
    return stmts;
}

PrintStatement *Parser::printStatement() {
    // <print-statement> -> print <id>
    Token printToken = tokenizer.getToken();
    if(printToken.getName() != "print"){
        die("Parser::printStatement", "Expected a print token, instead got", printToken);
    }
    // Getting a token and making sure it is a variable
    /*
    Token varName = tokenizer.getToken();
    if(!varName.isName()){
        die("Parser::printStatement", "Expected a var token, instead got", varName);
    }
     */
    std::cout << "ABOUT TO CALL TEST LIST" << std::endl;
    //ExprNode *rightHandSideExpr = testlist();
    std::vector<ExprNode*> rightHandSideExpr = testlist();
    std::cout << "FINISHED THE CALL TO  TEST LIST" << std::endl;

    //ExprNode *rightHandSideExpr = rel_expr();

    // Getting a token and making sure it a new line char


    /*
    Token tok = tokenizer.getToken();
    if (tok.isSemiColon())
        Token tok = tokenizer.getToken();
    if (!tok.isNewLine())
        die("Parser::printStatement", "Expected a New Line, instead got", tok);
        */

   // return new PrintStatement(varName.getName());
   std::cout << "Returning the finished print stmt!" << std::endl;
   return new PrintStatement(rightHandSideExpr);
}

ForStatement *Parser::forStatement() {
    // for(i = 0; i < num; i = i + 1){ <statements> }

    // for
    Token forToken =  tokenizer.getToken();
    if(!forToken.isForLoop()){
        die("Parser:ForStatement", "Expected a for token, instead got", forToken);
    }
    // (
    Token openParenToken = tokenizer.getToken();
    if(!openParenToken.isOpenParen()){
        die("Parser::ForStatement", "Expected an Open Paren Token, instead got", openParenToken);
    }
    // i = 0;
    AssignmentStatement *astmt1 = assignStatement();
    Token firstSemi = tokenizer.getToken();
    if(!firstSemi.isSemiColon()){
        die("Parser::ForStatement", "Expected a Semi Colon Token 1, instead got", firstSemi);
    }
    // i < num;
    ExprNode *rel_node = rel_expr();
    Token secondSemi = tokenizer.getToken();
    if(!secondSemi.isSemiColon()){
        die("Parser::ForStatement", "Expected a Semi Colon Token 2, instead got", secondSemi);
    }
    Token firstEOL = tokenizer.getToken();
    if(!firstEOL.isNewLine())
        die("Parser::ForStatement", "Expected a First EOL 1, instead got", firstEOL);
    // i = i + 1
    AssignmentStatement *astmt3 = assignStatement();
    // )
    Token closedParenToken = tokenizer.getToken();
    if(!closedParenToken.isCloseParen()){
        die("Parser::ForStatement", "Expected a Closed Paren Token, instead got", closedParenToken);
    }
    Token secondEOL = tokenizer.getToken();
    if(!secondEOL.isNewLine())
        die("Parser::ForStatement", "Expected a Second EOL 2, instead got", secondEOL);
    // {
    /*
    Token openBracketToken = tokenizer.getToken();
    if(!openBracketToken.isOpenBracket()){
        die("Parser::ForStatement", "Expected an Open Bracket Token, instead got", openBracketToken);
    }
     */
    // <statements>
    Statements *forstmts = statements();
    // }
    /*
    Token closeBracketToken = tokenizer.getToken();
    if(!closeBracketToken.isClosedBracket()){
        die("Parser::ForStatement", "Expected an Closed Bracket Token, instead got", closeBracketToken);
    }
     */

    return new ForStatement(astmt1, rel_node, astmt3, forstmts);
}

AssignmentStatement *Parser::assignStatement() {
    // <assigment-statement> -> <var> = <value>

    Token varName = tokenizer.getToken();
    /*
    if(varName.isNewLine()){
        Token varName = tokenizer.getToken();
    }
     */
    // <var>
    if (!varName.isName())
        die("Parser::assignStatement", "Expected a name token, instead got", varName);

    // =
    Token assignOp = tokenizer.getToken();
    if (!assignOp.isAssignmentOperator())
        die("Parser::assignStatement", "Expected an equal sign, instead got", assignOp);


    //ExprNode *rightHandSideExpr = rel_expr();
    ExprNode *rightHandSideExpr = test();

    Token endTok = tokenizer.getToken();
    if(!endTok.eol())
        die("Parser::assignment ", "Expected a new line, instead got ", endTok );

    return new AssignmentStatement(varName.getName(), rightHandSideExpr);
}

ExprNode *Parser::rel_expr() {
    // < rel-term { ( == , != ) < rel-term > }
    ExprNode *left = expr();
    Token tok = tokenizer.getToken();
    while (tok.isEqualToOperator() || tok.isNotEqualToOperator() || tok.isGreaterThanOperator() || tok.isLessThanOperator() || tok.isGreaterThanOrEqualToOperator() || tok.isLessThanOrEqualToOperator()){
        InfixExprNode *p = new InfixExprNode(tok);
	p->left() = left;
	p->right() = expr();
	left = p;
	tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}
/*
ExprNode *Parser::rel_term() {
    // < rel-primary > { ( > , >= , <, <= ) < rel-primary> }
    ExprNode *left = rel_primary();
    Token tok = tokenizer.getToken();

    while (tok.isGreaterThanOperator() || tok.isGreaterThanOrEqualToOperator() || tok.isLessThanOperator() || tok.isLessThanOrEqualToOperator()) {
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = rel_primary();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}
*/

ExprNode *Parser::expr() {
    // This function parses the grammar rules:

    // <expr> -> <term> { <add_op> <term> }
    // <add_op> -> + | -

    // However, it makes the <add_op> left associative.

    ExprNode *left = term();
    Token tok = tokenizer.getToken();
    while (tok.isAdditionOperator() || tok.isSubtractionOperator()) {
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = term();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}


ExprNode *Parser::term() {
    // This function parses the grammar rules:

    // <term> -> <primary> { <mult_op> <primary> }
    // <mult_op> -> * | / | %

    // However, the implementation makes the <mult-op> left associate.
    ExprNode *left = primary();
    Token tok = tokenizer.getToken();

    while (tok.isMultiplicationOperator() || tok.isDivisionOperator() || tok.isModuloOperator()) {
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = primary();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}

ExprNode *Parser::primary() {
    // This function parses the grammar rules:
    // <primary> -> [0-9]+
    // <primary> -> [_a-zA-Z]+
    // <primary> -> (<expr>)

    Token tok = tokenizer.getToken();
    if (tok.isWholeNumber() ) {
        return new WholeNumber(tok);
    } else if( tok.isStringS() ) {
	return new String(tok);
    } else if( tok.isName() ) {
        return new Variable(tok);
    } else if (tok.isOpenParen()) {
        ExprNode *p = expr();
        Token token = tokenizer.getToken();
        if (!token.isCloseParen())
            die("Parser::primary", "Expected close-parenthesis, instead got", token);
        return p;
    }
    die("Parser::primary", "Unexpected token", tok);

    return nullptr;  // Will not reach this statement!
}

std::vector<ExprNode *>Parser::testlist() {
    // <testlist> -> {',' <test>}*

    /*
    ExprNode *left = test();
    Token tok = tokenizer.getToken();
    while(tok.isComma()){
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = test();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
     */

    ExprNode *first = test();
    std::vector<ExprNode*> testVect;
    //ExprNode *first = test();
    //testVect.push_back(first);
    Token tok = tokenizer.getToken();
    while(tok.isComma()){
        testVect.push_back(first);
        first = test();
        tok = tokenizer.getToken();
    }
    testVect.push_back(first);

    tokenizer.ungetToken();
    return testVect;
}

ExprNode *Parser::test() {
    return rel_expr();
}

