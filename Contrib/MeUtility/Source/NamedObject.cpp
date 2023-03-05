#include "NamedObject.h"

NamedObject::NamedObject(const char*  argName)
{
	if(argName)
		name = argName;
}

NamedObject::NamedObject(const string &argName)
{
  name = argName;
}

NamedObject::NamedObject(const NamedObject &copy)
{
  if(this != &copy)
    name = copy.name;
}

NamedObject &NamedObject::operator=(const NamedObject &copy)
{
  if(this != &copy)
    name = copy.name;
  return *this;
}

void NamedObject::setName(const char   *nameArg)
{
  name = nameArg;
}

void NamedObject::setName(const string &nameArg)
{
  name = nameArg;
}

const string &NamedObject::getName() const
{
  return name;
}

NamedObject::~NamedObject()
{
  name.clear();
}


