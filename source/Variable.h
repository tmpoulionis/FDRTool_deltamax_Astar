#ifndef VARIABLE_H
#define VARIABLE_H

#include "Rigid.h"
#include "Domain.h"


class Variable : public Rigid
{
    public:
        Variable (string s):Rigid(s){}
        Object getValue() {return value;}
        void setValue(const Object &v){value=v;}

        void setDomain (const Domain &d) {domain = d;}
        Domain getDomain () {return domain;}
        string getFull();
        bool isValid (Object *);
        string toString() const;

        bool operator <= (const Variable &b)
        {
            cout<<"check"<<endl;
            return false;
        }


    protected:

    private:
        Object value;
        Domain domain;
};

#endif // VARIABLE_H
