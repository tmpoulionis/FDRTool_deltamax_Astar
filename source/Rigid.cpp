#include "Rigid.h"
#include<algorithm>

using namespace std;
Rigid::Rigid(string s)
{
    s.erase(remove(s.begin(), s.end(), '\n'),s.end());
    s.erase(remove(s.begin(), s.end(), '\r'),s.end());
    this->name = s;
}
void Rigid::add(const Object & o)
{
    parameters.push_back(o);
}
string Rigid::toString() const
{
    string s = name;

    if (parameters.size()>0)
    {
        s= s+"(";
        for (auto it=parameters.begin() ;it<parameters.end()-1;it++)
        {
            s =s + (*it).getDescription() +" ";
        }
        s =s + (*(parameters.end()-1)).getDescription() +")";
    }
    return s;
}
