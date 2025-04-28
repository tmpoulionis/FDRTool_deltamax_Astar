#ifndef ACTION_H
#define ACTION_H
#include <string>
#include <vector>
#include "Parameter.h"
#include "Precondition.h"
#include "Effect.h"
#include "Fact.h"


using namespace std;


class Action
{
    public:
        Action();
        Action (string);
        Parameter *getParameter (string);
        int getParameterPosition (string);
        bool addParameter(string);
        int setCost(int c) {cost=c;}
        int getCost() {return cost;}

        int getEffectsCount () {return effects.size();}
        Effect *getEffect (int i) {return effects[i];}
        string getName(){return name;}
        string toString ();
        void addPrecondition (Precondition *p) {precs.push_back(p);}
        std::vector<Precondition*>& getPreconditions() {return precs;}
        void addEffect (Effect *p) {effects.push_back(p);}
        bool operator== (const Action &a) {return this->name==a.name;}

        vector<vector<Parameter>> isApplicable( vector <Rigid> &,  vector <Fact> &) ;
        vector<vector<Parameter>> isApplicable(int, vector <Rigid> &,  vector <Fact> &,vector <Parameter>) ;
        int getParameterCount() {return parameters.size();}
        Parameter getParameter (int i) {return parameters[i];}

    protected:

    private:
        int cost = 1;
        string name;
        vector <Parameter> parameters;
        vector <Precondition *> precs;
        vector <Effect *> effects;

};

#endif // ACTION_H
