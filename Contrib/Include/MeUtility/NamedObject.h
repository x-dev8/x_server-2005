#ifndef NAMEDOBJECT_H
#define NAMEDOBJECT_H

#include <string>
using namespace std;

class NamedObject
{

  protected:
    string name;

  public:
    NamedObject(const char*  argName = NULL);
    NamedObject(const string &argName);
    NamedObject(const NamedObject &copy);
   ~NamedObject();

    NamedObject &operator=(const NamedObject &copy);
    void   setName(const char   *nameArg);
    void   setName(const string &name);

    const string &getName()     const;
};

#endif