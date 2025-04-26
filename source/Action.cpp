#include "Action.h"
#include "Parameter.h"

#include <algorithm>

#include "GroundedAction.h"
using namespace std;

Action::Action()
{
    //ctor
}
Action::Action(string s)
{
    s.erase(remove(s.begin(), s.end(), '\n'),s.end());
    s.erase(remove(s.begin(), s.end(), '\r'),s.end());
    this->name = s;
}
bool Action::addParameter(string s)
{
    auto it=find(parameters.begin(), parameters.end(), s);
    if (it != parameters.end())
        return false;

    parameters.push_back(Parameter(s));
    return true;
}

Parameter * Action::getParameter(string s)
{
    auto it=find(parameters.begin(), parameters.end(), s);
    if (it == parameters.end())
        return nullptr;
//    pos = it - parameters.begin();
    return &(*it);
}

string Action::toString()
{
    string s = name;
    s= s+"(";
    for (auto it=parameters.begin() ;it<parameters.end()-1;it++)
    {
        s =s + (*it).getDescription() +" ";
    }
    s =s + (*(parameters.end()-1)).getDescription() +")";
    s+="\nPrecs: ";
    for (auto it2=precs.begin() ;it2<precs.end()-1;it2++)
    {
        s =s + (*it2)->toString()+",";
    }
    s =s + (*(precs.end()-1))->toString();
    s+="\nEffects: ";
    for (auto it2=effects.begin() ;it2<effects.end()-1;it2++)
    {
        s =s + (*it2)->toString()+",";
    }
    s =s + (*(effects.end()-1))->toString();


    return s;

}
bool ground (vector <Parameter> mypar)
{
    for (auto it=mypar.begin(); it!=mypar.end();it++)
    {
        if (!(*it).isGround())
            return false;
    }
    return true;
}
int Action::getParameterPosition(string s)
{
    auto it=find(parameters.begin(), parameters.end(), s);
    if (it == parameters.end())
        return -1;
    return   it - parameters.begin();
}
vector<vector<Parameter>> Action::isApplicable(int N,vector <Rigid> &rigids, vector <Fact> &initial,vector <Parameter> par)
{
    vector<vector<Parameter>> solutions;


    if (N==precs.size())
    {
        /*cout<<"Applicable ";
    cout<<N<<"/"<<precs.size()<<" [";

    for (int i=0;i<par.size();i++)
        if (!par[i].isGround())
            cout<<"VAR ";
      else
            cout<<par[i].getValue().getDescription()<<" ";
    cout<<"]"<<endl;
*/
        if (!ground(par))
        {
            int i;
            for (i=0;par[i].isGround();i++);

        //    cout<<"Parameter "<<par[i].getDescription()<<"is not ground"<<endl;

            Domain *d = par[i].getDomain();

            for (int k=0;k<d->getSize();k++)
            {
              //  cout<<k<<"object is "<<d->getValue(k).getDescription()<<endl;
                vector <Parameter> mypar = par;
                if (mypar[i].setValue(d->getValue(k)))
                {
                    vector<vector<Parameter>> vvp = isApplicable(N,rigids, initial,mypar);
                    solutions.insert(solutions.end(),vvp.begin(),vvp.end());
                }
            }
/*
            vector<vector<Parameter>> vvp = isApplicable(N+1,rigids, initial,mypar);
            solutions.insert(solutions.end(),vvp.begin(),vvp.end());
            cout<<"Not ground"<<endl;*/
        }
        else
        {
            bool ok =true;
            for (int n=0;n<precs.size();n++)
            {
                if (precs[n]->isNegative())
                {
                    bool holds = false;

                    if (precs[n]->isRigid())
                    {
                        Rigid t(precs[n]->getName());
                        for (int i=0;i<precs[n]->getParameters();i++)
                        {
                            int kp = getParameterPosition(precs[n]->getParameter(i)->getName());
                            t.add(par[kp].getValue());
                        }
                        auto it = find (rigids.begin(),rigids.end(),t);
                        if (it!=rigids.end())
                        {
//                                cout<<"Found similar " <<t.toString()<<" vs "<<(*it).toString()<<endl;
                                holds = true;
                        }
                    }
                    else
                    {
                        Variable v(precs[n]->getName());
                        for (int i=0;i<precs[n]->getParameters();i++)
                        {
                            int kp = getParameterPosition(precs[n]->getParameter(i)->getName());
                            v.add(par[kp].getValue());
                        }

                        Fact f;
                        f.setVariable(&v);

                        Object ob;

                        if (precs[n]->isValueObject())
                            ob = precs[n]->getValue();
                        else
                        {
                            int kl = getParameterPosition(precs[n]->getValueP()->getName());
                            ob = par[kl].getValue();
                        }

                        f.setValue(&ob);


//                        v.setValue(precs[n]->getValue());

                        auto it = find (initial.begin(),initial.end(),f);
                        if (it!=initial.end())
                        {
                   //             cout<<"Found similar " <<f.toString()<<" vs "<<(*it).toString()<<endl;
                                holds = true;
                        }

                     //   cout<<"Gotcha "<<f.toString()<<endl;
                    }


                    if (holds)
                    {
                        ok=false;
                        break;
                    }

                }

            }

            if (ok)
                solutions.push_back(par);
        }
            return solutions;


    }
    if (precs[N]->isNegative())
    {
      //  cout<<"Negative prec"<<endl;
        return isApplicable(N+1,rigids,initial,par);
    }
    else if (precs[N]->isRigid())
    {
     //   cout<<"Rigid"<<endl;
        for (auto r = rigids.begin();r!=rigids.end();r++)
        {
            if (*precs[N]>= (*r))
            {
                bool canDo=true;
                vector <Parameter> mypar = par;
                Rigid rig = *r;
              //  cout<<"found rigid"<<endl;
                for (int k =0;k<precs[N]->getParameters();k++)
                {
                    int kp = getParameterPosition(precs[N]->getParameter(k)->getName());
                    if (mypar[kp].isGround() && (mypar[kp].getValue())!= rig.getParameter(k))
                    {
                        canDo=false;
                        break;
                    }
                    if (!mypar[kp].isGround())
                    {
                        bool b =mypar[kp].setValue(rig.getParameter(k));
                        if (!b)
                        {
                            canDo=false;
                            break;
                        }
                    }
                }
                if (canDo)
                {
                    vector<vector<Parameter>> vvp = isApplicable(N+1,rigids, initial,mypar);
                    solutions.insert(solutions.end(),vvp.begin(),vvp.end());
                }
            }
        }
    }
    else
    {
        for (auto v = initial.begin();v!=initial.end();v++)
        {
            if (*precs[N]>=(*(*v).getVariable()))
            {
                bool canDo=true;
                vector <Parameter> mypar = par;
                for (int k =0;k<precs[N]->getParameters();k++)
                {
                    int kp = getParameterPosition(precs[N]->getParameter(k)->getName());
                    if (mypar[kp].isGround() && (mypar[kp].getValue())!= (*v).getVariable()->getParameter(k))
                    {
                        canDo=false;
                        break;
                    }
                    if (!mypar[kp].isGround())
                    {
                        bool b =mypar[kp].setValue((*v).getVariable()->getParameter(k));
                        if (!b)
                        {
                            canDo=false;
                            break;
                        }
                    }
                }
                int kl;
                if (precs[N]->isValueObject())
                {
                    if (precs[N]->getValue() != (*(*v).getValue()))
                        canDo=false;
                }
                else
                {
                    kl = getParameterPosition(precs[N]->getValueP()->getName());
                    if (mypar[kl].isGround() && mypar[kl].getValue()!= (*(*v).getValue()))
                        canDo=false;
                    if (!mypar[kl].isGround())
                        if (!mypar[kl].setValue(*(*v).getValue()))
                            canDo=false;
                }
                if (canDo)
                {
                    vector<vector<Parameter>> vvp = isApplicable(N+1,rigids, initial,mypar);
                    solutions.insert(solutions.end(),vvp.begin(),vvp.end());
                }
            }
        }
    }
    return solutions;
}
vector<vector<Parameter>> Action::isApplicable(vector <Rigid> &rigids, vector <Fact> &initial)
{
    vector <Parameter> mypar  = parameters;
    return isApplicable(0,rigids,initial,mypar);
}
