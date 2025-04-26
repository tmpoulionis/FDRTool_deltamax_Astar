#include "FDRSTate.h"
#include <unordered_map>
#include <limits>
#include <set>
#include <string>
#include <vector>

using namespace std;

FDRSTate::FDRSTate( vector <Action> &a, vector <Rigid> &r,vector <Fact>s):rigids(r),actions(a)
{
//    rigids=r;
  //  actions=a;
    vars = s;
}

vector<GroundedAction> FDRSTate::findForks()
{
    vector<vector<Parameter>> solutions;
    vector<GroundedAction> forks;

    for (int i =0;i<actions.size();i++)
    {
        solutions = actions[i].isApplicable(rigids,vars);
        for (int k=0;k<solutions.size();k++)
            forks.push_back(GroundedAction(&actions[i],solutions[k]));
    }
    return forks;
}

vector<FDRSTate *> FDRSTate::expand()
{
    vector<FDRSTate *> children;
    vector<GroundedAction> gacts;

    gacts = findForks();

    for (int i=0;i<gacts.size();i++)
        children.push_back(getSuccessorState(gacts[i]));
    return children;
}

FDRSTate *FDRSTate::getSuccessorState(GroundedAction a)
{
    FDRSTate *r = new FDRSTate(*this);

    r->addAction(a.toString());

  //  cout<<r.toString()<<endl;

    for (int i=0;i<a.getEffectsCount();i++)
    {
        Fact f = a.getEffect(i);



      //  cout<<"Searcing for "<<f.toString()<<endl;
        for (auto it = r->vars.begin();it< r->vars.end();it++)
        {
         //   cout<<(*it).toString();
            if ( *(*it).getVariable() == *f.getVariable())
            {
              //  cout<<" YES"<<endl;
                (*it).setValue(f.getValue());
            }
//            else
  //              cout<<" NO"<<endl;

        }
    }
    return r;
}
string FDRSTate::toString()const
{
    string s="";
    if (vars.size()>0)
    {
        s="[";
        for (int i=0;i<vars.size()-1;i++)
            s+=vars[i].toString()+",";
        s+=vars[vars.size()-1].toString()+"]";
    }
    return s;
}

bool operator == (const FDRSTate a, const FDRSTate b)
{
    for (int i=0;i<b.vars.size();i++)
    {
        bool found =false;
        for (int j = 0; !found && j<a.vars.size();j++)
        {
            if (b.vars[i]==a.vars[j])
                found =true;
        }
        if (!found)
        {
           // cout<<"not found"<<endl;
            return false;
        }
    }
    return true;

//    return a==b;
}
unsigned long long FDRSTate::getKey() const
{
    unsigned long long k=0;

    for (int i=0;i<vars.size();i++)
        k+= vars[i].getNumber() * (vars[i].getDomainSize(),i);

    //cout<<k<<endl;
    return k;
}
/*
bool operator >= (pair<const FDRSTate s, bool b> s43,const FDRSTate s2)
{

}
*/

double FDRSTate::heuristic(State *goal) {
    FDRSTate* goalState = dynamic_cast<FDRSTate*>(goal);

    unordered_map<Fact, double> deltaMax;
    set<Fact> U;

    // Initialize all facts with deltaMax = 0
    for(const Fact& fact : vars) {
        deltaMax[fact] = 0;
        U.insert(fact);
    }

    // Generate all facts for the problem
    vector<Fact> allFacts;
    for (const Fact& fact : vars) {
        Variable* var = fact.getVariable();
        for (const Object& obj : var->getDomain().getObjects()) {
            allFacts.emplace_back(var, &obj);
        }
    }

    for (const Fact& fact : allFacts) {
        if (!deltaMax.count(fact)) {
            deltaMax[fact] = std::numeric_limits<double>::infinity();
        }
    }
    
    bool updated;
    do {
        updated = false;
        for (Action& action : actions) {
            // Get all valid parameter combinations for each action
            auto allParams = action.isApplicable(rigids, vars);
            for (auto& params : allParams) {
                GroundedAction ga(&action, params);

                // Check if preconditions are satisfied
                bool preconditionsMet = true;
                for (const Fact& pre : ga.getPreconditions()) {
                    if(!U.count(pre)) {
                        preconditionsMet = false;
                        break;
                    }
                }

                if (preconditionsMet) {
                    double actionCost = 1;
                    double maxPreconditionCost = 0;

                    // Find the most expensive precondition to execute this action
                    for (const Fact& pre : ga.getPreconditions()) {
                        maxPreconditionCost = std::max(maxPreconditionCost, deltaMax[pre]);
                    }

                    for (const Fact& eff : ga.getEffects()) {
                        double newCost = actionCost + maxPreconditionCost;
                        if (newCost > deltaMax[eff]) {
                            deltaMax[eff] = newCost;
                            updated = true;
                        }
                        U.insert(eff);
                    }
                } 
            }
        }
    } while (updated);

    double maxCost = 0;
    for (const Fact& goalFact : goalState->vars) {
        maxCost = std::max(maxCost, deltaMax[goalFact]);
    }

    return maxCost;
}