#ifndef GROUNDEDACTION_H
#define GROUNDEDACTION_H
#include <string>
#include <vector>
#include "Parameter.h"
#include "Action.h"

using namespace std;

class GroundedAction
{
    public:
        GroundedAction(Action *act, vector <Parameter> p)
        {
            a = act;
            mypar = p;
        }

        int getEffectsCount() {return a->getEffectsCount();}

        Fact getEffect(int i);


        string toString();

    protected:

    private:
        Action *a;
        vector <Parameter> mypar;
};

#endif // GROUNDEDACTION_H
