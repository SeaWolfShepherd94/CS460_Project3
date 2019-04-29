#include <iostream>

struct TypeDescriptor {
    // The base class for datatype descriptors.
    
    // This enum can expand to include additional types.
    enum types {INTEGER, DOUBLE, BOOL, STRING};

    TypeDescriptor(types type): _type{type} {}

    types &type() { return _type; }

    virtual void value(int v) = 0;

    virtual ~TypeDescriptor() {}
	
private:
    types _type;
};

struct NumberDescriptor: public TypeDescriptor {
    // Number descriptor includes integer, double, and boolean datatypes.

    NumberDescriptor(types descType):  TypeDescriptor(descType) {}
    virtual void value(int v) {_intValue = v;}
    virtual int value() {return _intValue;}
private:
    int _intValue;
};

struct StringDescriptor: public TypeDescriptor {
    // String Descriptor

    StringDescriptor(types descType):  TypeDescriptor(descType), _stringValue{""} {}
    virtual void value(std::string v) {_stringValue = v;}
    virtual std::string value() {return _stringValue;}
private:
    std::string _stringValue;
};

void printValue(TypeDescriptor *desc) {
    if ( desc->type() == TypeDescriptor::STRING ) {
        StringDescriptor *nDesc = dynamic_cast<StringDescriptor *>(desc);
	if( nDesc == nullptr )
            return;
        if( nDesc->type() == TypeDescriptor::STRING )
	    std::cout << nDesc->value() << std::endl;
    }
    NumberDescriptor *nDesc = dynamic_cast<NumberDescriptor *>(desc);
    // dynamic_cast will return a nullptr if
    // desc is not of datatype NumberDescritpr.
    if( nDesc == nullptr )
        return;

    // desc must have been of type NumberDescriptr
    if( nDesc->type() == TypeDescriptor::INTEGER )
        std::cout << nDesc->value() << std::endl;
}
