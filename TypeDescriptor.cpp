#include "TypeDescriptor.hpp"

TypeDescriptor::TypeDescriptor(std::string variableName): _name{variableName} {}

IntegerTypeDescriptor::IntegerTypeDescriptor(std::string variableName, int value): _name{variableName}, _value{value} {}

IntegerTyepDescriptor::IntegerTypeDescriptor(std::string variableName): _name{variableName} {}

std::string IntegerTypeDescriptor::name() {
    return _name;
}

int IntegerTypeDescriptor::intValue() {
    return _value;
}
