#include "Effect.h"

Effect::Effect(string s):Precondition(s)
{

}

string Effect::toString()
{
    string s=getName();
    if (parameters.size()>0)
    {
        s= s+"(";
        for (auto it=parameters.begin() ;it<parameters.end()-1;it++)
        {
            s =s + (*it)->getName()+",";
        }
        s =s + (*(parameters.end()-1))->getName() +")";
    }
    if (valueisObject)
        s+="<-"+value.getDescription();
    else
        s+="<-"+valueP->getName();
    return s;

}
