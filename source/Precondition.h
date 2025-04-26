#ifndef PRECONDITION_H
#define PRECONDITION_H

#include "Rigid.h"
#include "Parameter.h"
#include "Variable.h"
//#include "Action.h"

class Precondition : public Rigid
{
    public:
        Precondition(string);
        Object getValue() {return value;}
   //     void setValue(const Object &o) {value=o;}
        bool isRigid () {return rigid;}
        void setRigid (bool v) {rigid = v;}
 //       void setAction (Action *p) {action =p;}
   //     Action *getAction () {return action;}
        bool addParameter(Parameter *);
        Parameter *getParameter(int );
        int getParameters () {return parameters.size();}

        string toString();
        Variable * getVariable () {return variable;}
        void setVariable (Variable *v) {variable =v;}

        bool isValueObject(){return valueisObject;}
        void setValue (const Object &value)
        {
            this->value=value;
            valueisObject=true;
        }
        void setValue (Parameter *value)
        {
            this->valueP=value;
            valueisObject=false;
        }
        void setNegative (bool s) {this->negation=s;}
        bool isNegative() {return negation;}

        bool operator>= (Rigid &v)
        {
            return (name==v.getName());
        }

   /*     bool operator == (const Rigid r)
        {
            if (name!=r.getName())
                return false;
            return true;

        }
*/
        Parameter *getValueP() {return valueP;}
        vector <Parameter *> &getParameterVector() {return parameters;}

    protected:
        vector<Parameter *> parameters;
        Object value;

        Parameter *valueP;
        bool valueisObject;

        Variable *variable;
        bool rigid;
        bool negation=false;
};

#endif // PRECONDITION_H
