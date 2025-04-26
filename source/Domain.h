#ifndef DOMAIN_H
#define DOMAIN_H
#include <string>
#include <vector>
#include "Object.h"

#include <iostream>
#include <algorithm>
using namespace std;

class Domain
{
    public:
        Domain (){}
        Domain(string);
        void add (const Object &);
        void del(const Object &);

        void add (const Domain &);
        void del(const Domain &);


        unsigned int getSize() {return values.size();}
        int getpos (Object v)
        {
            auto it = find(values.begin(),values.end(),v);
            if (it ==values.end())
                return -1;
            return it-values.begin();
        }

        string toString();

        string getName () {return name;}

        bool operator == (string s)
        {
            return (s==name);
        }
        bool isValid (string );

        Object getValue(int i) {return values[i];}
        bool operator == (Domain d)
        {
            return d.name==name;
        }
        bool operator<= (Domain d);
    private:
        string name;
        vector <Object > values;
};

#endif // DOMAIN_H
