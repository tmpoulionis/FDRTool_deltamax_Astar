#include "Precondition.h"
#include <algorithm>
using namespace std;

Precondition::Precondition(string s):Rigid(s)
{
}

Parameter *Precondition::getParameter(int k)
{
    return parameters[k];

}


bool Precondition::addParameter(Parameter *p)
{
    auto it=find(parameters.begin(), parameters.end(), p);
    if (it != parameters.end())
        return false;
    parameters.push_back(p);
    return true;
}
string Precondition::toString()
{
    string s="";
    if (negation)
        s="not ";
    s+=""+ getName();

    if (parameters.size()>0)
    {
        s= s+"(";
        for (auto it=parameters.begin() ;it<parameters.end()-1;it++)
        {
            s =s + (*it)->getName()+" ";
        }
        s =s + (*(parameters.end()-1))->getName() +")";
    }
    if (!rigid)
        if (valueisObject)
            s+="="+value.getDescription();
        else
            s+="="+valueP->getName();
    return s;

}
