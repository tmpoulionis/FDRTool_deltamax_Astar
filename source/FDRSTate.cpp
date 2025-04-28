#include "FDRSTate.h"
#include <limits>
#include <set>
#include <string>
#include <vector>
#include <unordered_map>

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

int FDRSTate::HeuristicDeltaMax(const std::vector<Fact>& goal) {

    unordered_map<string, int> deltaMax; // Like a python dictionary
    set<string> U;

    // Get all possible facts and initialize them to infinity
    for (Fact& fact : vars) {
        Variable* var = fact.getVariable();
        Domain domain = var->getDomain();
        for (int i=0; i<domain.getSize(); i++) {
            Object value = domain.getValue(i);
            string fact_str = var->getName() + "=" + value.getDescription();
            deltaMax[fact_str] = std::numeric_limits<int>::max();
        }
    }

    for (Fact& fact : vars) {
        string fact_str = fact.toString();
        deltaMax[fact_str] = 0;
        U.insert(fact_str);
    }
    
    bool updated;
    do {
        updated = false;
        for (Action& action : actions) {
            // Get all valid parameter combinations for each action
            auto allParams = action.isApplicable(rigids, vars);
            for (auto& params : allParams) {
                GroundedAction ga(&action, params);
                std::vector<Fact> preconditions = ga.getPreconditions();

                // Check if preconditions are satisfied
                bool precsMet = true;
                int maxPreconditionCost = 0;
                for (const Fact& prec : preconditions) {
                    string precStr = prec.toString();
                    if (!U.count(precStr)) {
                        precsMet = false;
                        break;
                    }
                    maxPreconditionCost = std::max(maxPreconditionCost, deltaMax[precStr]); // Find the most expensive precondition to execute this action
                }

                if (precsMet) {
                    int actionCost = action.getCost();

                    for (int i=0; i < ga.getEffectsCount(); i++) {
                        Fact eff = ga.getEffect(i);
                        string effStr = eff.toString();

                        int newCost = actionCost + maxPreconditionCost;

                        if (!deltaMax.count(effStr)) {
                            deltaMax[effStr] = std::numeric_limits<int>::max();
                        }

                        if (newCost < deltaMax[effStr]) {
                            deltaMax[effStr] = newCost;
                            U.insert(effStr);
                            updated = true;
                        }
                    }
                } 
            }
        }
    } while (updated);

    int maxCost = 0;
    for (const Fact& goalFact : goal) {
        string goalStr = goalFact.toString();
        if (!deltaMax.count(goalStr)) {
            return std::numeric_limits<int>::max(); // Unreachable
        }
        maxCost = std::max(maxCost, deltaMax[goalStr]);
    }

    return maxCost;
}