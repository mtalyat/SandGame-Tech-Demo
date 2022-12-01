#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <typeinfo>

class Object
{
public:
	Object() {}
	virtual ~Object(){}

	virtual std::string toString() const { return typeid(*this).name(); }
};

#endif
