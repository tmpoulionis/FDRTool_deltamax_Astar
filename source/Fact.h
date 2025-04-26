#ifndef FACT_H
#define FACT_H
#include "Variable.h"
#include "Object.h"

class Fact
{
    public:
        Fact();

        void setVariable (Variable *v) {var=v;}
        Variable * getVariable () {return var;}

        void setValue (Object *v) {val=v;}
        Object *getValue () {return val;}

        bool operator == (const Fact f)const
        {
            if (*val!=*f.val)
                return false;
            return *var == *(f.var);
            //return 1;
        }

        string toString() const
        {
            return var->toString()+"=" +val->getDescription();
        }

        unsigned getNumber()const
        {
            return var->getDomain().getpos(*val);

        }
        unsigned getDomainSize() const
        {
            return var->getDomain().getSize();
        }

    protected:

    private:
        Variable *var;
        Object *val;
};

#endif // FACT_H
