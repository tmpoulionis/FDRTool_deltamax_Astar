#include "Parameter.h"
#include <algorithm>
using namespace std;

Parameter::Parameter()
{
    domain = nullptr;
    //ctor
}

string Parameter::getDescription()
{
    string s;
    s = name + " [";
    if (domain == nullptr)
        s+="void]";
    else
        s+=domain->getName()+ "]";
    return s;
}

Parameter::Parameter(string s)
{
    s.erase(remove(s.begin(), s.end(), '\n'),s.end());
    s.erase(remove(s.begin(), s.end(), '\r'),s.end());
    this->name = s;
    domain = nullptr;
  //  value=nullptr;
    ground = false;
}

