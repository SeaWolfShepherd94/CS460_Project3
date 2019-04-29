//
// Created by Ali A. Kooshesh on 2/5/19.
//

#include <iostream>
#include "SymTab.hpp"

TypeDescriptor::~TypeDescriptor(){}
/*
void SymTab::setValueFor(std::string vName, int value) {
    // Define a variable by setting its initial value.
    std::cout << vName << " <- " << value << std::endl;
    intSymTab[vName] = value;
}

void SymTab::setStringValueFor(std::string vName, std::string value) {
    std::cout << vName << " <- " << value << std::endl;
    stringSymTab[vName] = value;
}

bool SymTab::isDefined(std::string vName) {
    return intSymTab.find(vName) != intSymTab.end() || stringSymTab.find(vName) != stringSymTab.end();
}

bool SymTab::isString(std::string vName) {
    return stringSymTab.find(vName) != stringSymTab.end();
}

int SymTab::getValueFor(std::string vName) {
    if( ! isDefined(vName)) {
        std::cout << "SymTab::getValueFor: " << vName << " has not been defined.\n";
        exit(1);
    }
    std::cout << "SymTab::getValueFor: " << vName << " contains " << intSymTab.find(vName)->second << std::endl;
    return intSymTab.find(vName)->second;
}

std::string SymTab::getStringValueFor(std::string vName) {
    if( ! isDefined(vName)) {
        std::cout << "SymTab::getValueFor: " << vName << " has not been defined.\n";
        exit(1);
    }
    std::cout << "SymTab::getValueFor: " << vName << " contains " << stringSymTab.find(vName)->second << std::endl;
    return stringSymTab.find(vName)->second;
}
*/

//SymTab for INTS
void SymTab::setValueFor(std::string vName, int value) {
    // Define a variable by setting its initial value.
    std::cout << vName << " <- " << value << std::endl;
    NumberTypeDescriptor *desc = new NumberTypeDescriptor(TypeDescriptor::INTEGER);
    desc->value.intValue =  value;
    symTab[vName] = desc;
}

void SymTab::setValueFor(std::string vName, std::string value) {
    // Define a variable by setting its initial value.
    std::cout << vName << " <- " << value << std::endl;
    StringTypeDescriptor *desc = new StringTypeDescriptor(TypeDescriptor::STRING);
    desc->stringValue = value;
    symTab[vName] = desc;
}

bool SymTab::isDefined(std::string vName) {
    return symTab.find(vName) != symTab.end();
}

TypeDescriptor* SymTab::getValueFor(std::string vName) {
    if( ! isDefined(vName)) {
        std::cout << "SymTab::getValueFor: " << vName << " has not been defined.\n";
        exit(1);
    }
    NumberTypeDescriptor *nDesc = dynamic_cast<NumberTypeDescriptor*>(symTab.find(vName)->second);
    if(nDesc == nullptr){
        StringTypeDescriptor *nDesc = dynamic_cast<StringTypeDescriptor*>(symTab.find(vName)->second);
        std::cout << "SymTab::getValueFor: " << vName << " contains " << nDesc->stringValue << std::endl;
        return symTab.find(vName)->second;
    }
    if(nDesc->type() == TypeDescriptor::INTEGER) {
        std::cout << "SymTab::getValueFor: " << vName << " contains " << nDesc->value.intValue << std::endl;
    }
    else if(nDesc->type() == TypeDescriptor::BOOL){
        std::cout << "SymTab::getValueFor " << vName << " contains " << nDesc->value.boolValue << std::endl;
    }
    return symTab.find(vName)->second;
}
