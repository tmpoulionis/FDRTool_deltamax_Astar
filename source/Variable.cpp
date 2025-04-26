#include "Variable.h"
#include <string>
using namespace std;

string Variable::getFull()
{
    string s=getName();
    if (parameters.size()>0)
    {
        s= s+"(";
        for (auto it=parameters.begin() ;it<parameters.end()-1;it++)
        {
            s =s + (*it).getDescription()+",";
        }
        s =s + (*(parameters.end()-1)).getDescription() +")";
    }
    return s;
}


bool Variable::isValid(Object *o)
{
    return domain.isValid(o->getDescription());
}

string Variable::toString() const
{
//    cout<<"WHAT"<<endl;
    string s = Rigid::toString();
    s+="="+value.getDescription();
    return s;
}
