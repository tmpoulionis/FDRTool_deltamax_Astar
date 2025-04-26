#ifndef PARAMETER_H
#define PARAMETER_H
#include "Domain.h"

class Parameter
{
    public:
        Parameter();
        Parameter(string);
        void setDomain (Domain *d) {domain=d;}
        Domain *getDomain() {return domain;}

        string getName() {return name;}

        bool operator == (string s)
        {
            return (s==name);
        }
        string getDescription();

        bool setValue (Object o)
        {
            if (!domain->isValid(o.getDescription()))
                return false;
            value=o;
            ground=true;
            return true;
        }
        bool isGround(){return ground;}
        Object getValue() {return value;}
    protected:

    private:
        string name;
        Domain *domain;
        Object value;
        bool ground;
};

#endif // PARAMETER_H
