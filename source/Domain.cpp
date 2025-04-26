#include "Domain.h"
#include <algorithm>
#include <iostream>
using namespace std;

Domain::Domain(string s)
{
    s.erase(remove(s.begin(), s.end(), '\n'),s.end());
    s.erase(remove(s.begin(), s.end(), '\r'),s.end());
    this->name = s;
}
void Domain::add(const Object &o)
{
 //   cout<<"Adding: "<<o->getDescription()<<endl;

    if (find(values.begin(),values.end(), o) == values.end())
        values.push_back(o);
}
void Domain::add(const Domain &d)
{
    for (auto it = d.values.begin(); it!=d.values.end();it++)
        add(*it);
}

void Domain::del(const Object &o)
{
 //   cout<<"Removing: "<<o->getDescription()<<endl;

    auto it = find(values.begin(),values.end(), o);

    if (it!= values.end())
        values.erase(it);
   //     values.push_back(o);
}
void Domain::del(const Domain &d)
{
    for (auto it = d.values.begin(); it!=d.values.end();it++)
        del(*it);
}

bool Domain::isValid(string s)
{
   // cout<<"Checking for valid "<<s<<endl;

    auto it=find(values.begin(), values.end(), s);
    if (it == values.end())
    {
     //   cout<<"false"<<endl;
        return false;
    }
   // cout<<"found"<<endl;
    return true;
}
bool Domain::operator<=(Domain o)
{
    for (auto it = values.begin(); it!=values.end();it++)
    {
        auto it2=find(o.values.begin(), o.values.end(), (*it).getDescription());
        if (it2 == o.values.end())
            return false;
    }

    return true;
}

string Domain::toString()
{
    string s = name;
    s= s+"(";
    for (vector <Object>::iterator it=values.begin() ;it<values.end()-1;it++)
    {
        s =s + (*it).getDescription() +" ";
    }
    s =s + (*(values.end()-1)).getDescription() +")";
    return s;
}
