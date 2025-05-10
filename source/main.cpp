#include <iostream>
#include <sstream>
#include <vector>
#include "Domain.h"
#include "Variable.h"
#include "Action.h"
#include "Effect.h"
#include "Fact.h"
#include <algorithm>
#include <iterator>
#include <cstring>
#include <fstream>
#include "GroundedAction.h"
#include "FDRSTate.h"
#include <queue>
#include <unordered_map>
#include <stack>
#include "SearchAlgos.h"
#include <ctime>

using namespace std;

void applyAction (vector <Rigid> &rigids, vector<Fact> initial,vector <Action> &actions)
{

    vector<GroundedAction> forks;
    FDRSTate init (actions,rigids,initial);
    forks = init.findForks();

   // cout<<init.toString()<<endl;
    cout<<"Found "<<forks.size()<<" forks"<<endl;
    for (auto it = forks.begin(); it<forks.end();it++)
        cout<<(*it).toString()<<endl;

  //  forks[0].getEffect(2);

/*
    vector<FDRSTate *> child = init.expand();

    cout<<"Found "<<child.size()<<" states"<<endl;
    for (int i=0;i<child.size();i++)
    {
   //     cout<<"Action "<<forks[i].toString()<<endl;
        cout<<child[i]->toString()<<endl;
    }

*/

}
/*
namespace std {
  template <>
  class hash<FDRSTate>
  {
      public:
        size_t operator()(const FDRSTate &a) const
        {
            return 5;//a.getKey();
        }
  };
}


//template <typename X>
FDRSTate *BFS(FDRSTate *initial,FDRSTate *goal, long long &examined, long long &mem)
{
    queue<FDRSTate *> agenda;
//    vector <FDRSTate > closed;
    unordered_map <FDRSTate, bool> closed;
    agenda.push(initial);
    examined=0;
    mem=1;

  //  cout<<"BFS ISN"<<endl;
    while (agenda.size()>0)
    {
        if (agenda.size() + closed.size() > mem)
            mem = agenda.size() + closed.size();
        examined++;
        FDRSTate *s = agenda.front();


   //     cout<<s->toString()<<endl<<endl;

        agenda.pop();
        if (*s==*goal)
        {
          //  cout<<"Same"<<endl;
            return s;
        }
//        closed.push_back(*s);
        closed[*s]=true;
        vector<FDRSTate *> children =s->expand();
        for (unsigned int i=0;i<children.size();i++)
        {
            auto it = find(closed.begin(),closed.end(),*children.at(i));
            if (it==closed.end())
                agenda.push(children.at(i));


        }

//          if (!closed[*children.at(i)])
 //               agenda.push(children.at(i));
    }
    return nullptr;
}
FDRSTate *DFS(FDRSTate *initial,FDRSTate *goal, long long &examined, long long &mem)
{
    stack<FDRSTate *> agenda;
    vector <FDRSTate > closed;
//    unordered_map <FDRSTate, bool> closed;
    agenda.push(initial);
    examined=0;
    mem=1;

  //  cout<<"BFS ISN"<<endl;
    while (agenda.size()>0)
    {
        if (agenda.size() + closed.size() > mem)
            mem = agenda.size() + closed.size();
        examined++;
        FDRSTate *s = agenda.top();


   //     cout<<s->toString()<<endl<<endl;

        agenda.pop();
        if (*s==*goal)
        {
          //  cout<<"Same"<<endl;
            return s;
        }
        closed.push_back(*s);

      //  closed[*s]=true;
        vector<FDRSTate *> children =s->expand();
        for (unsigned int i=0;i<children.size();i++)
        {
            auto it = find(closed.begin(),closed.end(),*children.at(i));
            if (it==closed.end())
                agenda.push(children.at(i));


        }

//          if (!closed[*children.at(i)])
 //               agenda.push(children.at(i));
    }
    return nullptr;
}


*/

void removeLeadingLines(string &s)
{
    while (s[0]=='\n' || s[0]=='\r')
    {
    //    cout<<"LNL"<<endl;
        s.erase(0,1);
    }
}

void removeComments(string &s)
{
    removeLeadingLines(s);
    int commentStart = s.find("//");
    if (commentStart < s.size())
    {
    //    cout<<"Old string=."<<s<<"."<<endl;
        int commentEnd = s.find('\n',commentStart);

        if (commentEnd == string::npos)
            commentEnd = s.size()-1;
  //      cout<<"found comments at char "<<commentStart<<" to "<<commentEnd<<endl;
   //     string d =s;
   //     d.erase(10,20);
 //       cout<<"Test string= ."<<s<<"."<<endl<<endl;

        s.erase(commentStart,commentEnd-commentStart+1);
 //       cout<<"New string= ."<<s<<"."<<endl<<endl;

    }
}

string readNext(ifstream &f)
{
    string s;
    getline(f,s,';');

    while (s!="")
    {
        removeComments(s);
        s.erase(remove(s.begin(), s.end(), ' '),s.end());
        s.erase(remove(s.begin(), s.end(), '\n'),s.end());
        s.erase(remove(s.begin(), s.end(), '\r'),s.end());

        if (s!="")
            return s;
        getline(f,s,';');
    }
    return "";
}

int main(int argc, char *argv[])
{
    vector <Object> objects;
    vector <Domain> domains;
    vector <Rigid> rigids;
    vector <Variable> variables;
    vector <Action> actions;

    vector<Fact> initial,goals;
    string s;

    string filename;

    if (argc > 1)
       filename = argv[1];
    else
    {
        cout<<"Filename to open: ";
        cin>>filename;
    }
    ifstream f;  // Δηλώνουμε ένα ρεύμα εισόδου f
    cout<<"Opening "<<filename<<endl;
    f.open(filename); // Προσπαθούμε να ανοίξουμε το αρχείο "a.txt"
    if (!f.is_open()) // Η is_open() επιστρέφει true αν το αρχείο είναι ανοικτό
    {
        cerr<<"Could not open file"<<endl;
        return 1;
    }

    clock_t start,finish;
    start = clock();

/*    getline(f,s,';');
    removeComments(s);
    s.erase(remove(s.begin(), s.end(), ' '),s.end());
    s.erase(remove(s.begin(), s.end(), '\n'),s.end());
    s.erase(remove(s.begin(), s.end(), '\r'),s.end());
*/

    s=readNext(f);
    while (s!="")
    {

  //      cout<<"\'"<<s<<"\'"<<endl;

    if (s.find("goals=")!=string::npos)
    {
//        cout<<"Goals: ";
        stringstream check(s);
        string name;
        getline(check,name,'{');
        getline(check,name,'}');

//        cout<<name<<endl;
        stringstream check2(name);
        string f;

        while (getline (check2,f,','))
        {
            stringstream ss(f);
            string fname, fval;

            getline (ss,fname,'<');
            getline (ss,fval,'-');
            getline (ss,fval,',');

  //          cout<<fname<<"     =     "<<fval<<endl;

            Variable *v=nullptr;
            Object *ob=nullptr;

            for (auto it=variables.begin(); it<variables.end();it++)
            {
                if ((*it).getFull()==fname)
                    v = &(*it);
            }
            for (auto it=objects.begin(); it<objects.end();it++)
            {
                if ((*it).getDescription()==fval)
                    ob = &(*it);
            }

            if (v==nullptr)
            {
                cerr<<"Error!!! In goals, unknown variable "<<fname<<"!"<<endl;
                return 1;
            }
            if (ob==nullptr)
            {
                cerr<<"Error!!! In goals, value "<<fval<<" for variable "<<fname<<" has not been defined!"<<endl;
                return 1;
            }

            if (!v->isValid(ob))
            {
                cerr<<"Error!!! In goals, value "<<fval<<" is not valid for variable "<<fname<<"!"<<endl;
                return 1;
            }

            Fact f;
            f.setVariable(v);
            f.setValue(ob);


            for (auto it=goals.begin(); it<goals.end();it++)
            {
                if (*((*it).getVariable()) == *v)
                {
                    cerr<<"Error!!! In goals, duplicate value for "<<fname<<"!"<<endl;
                    return 1;
                }
            }
            goals.push_back(f);
        }
        if (goals.size()!=variables.size())
        {
            cerr<<"Warning!!! The problem may have multiple goal states! The assignments in the goals are less than the state variables in the problem!"<<endl;
        }
    }

    else

    if (s.find("initial=")!=string::npos)
    {
//        cout<<"Initial State : ";
        stringstream check(s);
        string name;
        getline(check,name,'{');
        getline(check,name,'}');

//        cout<<name<<endl;
        stringstream check2(name);
        string f;

        while (getline (check2,f,','))
        {
            stringstream ss(f);
            string fname, fval;

            getline (ss,fname,'<');
            getline (ss,fval,'-');
            getline (ss,fval,',');

  //          cout<<fname<<"     =     "<<fval<<endl;

            Variable *v=nullptr;
            Object *ob=nullptr;

            for (auto it=variables.begin(); it<variables.end();it++)
            {
                if ((*it).getFull()==fname)
                    v = &(*it);
            }
            for (auto it=objects.begin(); it<objects.end();it++)
            {
                if ((*it).getDescription()==fval)
                    ob = &(*it);
            }

            if (v==nullptr)
            {
                cerr<<"Error!!! In initial state, unknown variable "<<fname<<"!"<<endl;
                return 1;
            }
            if (ob==nullptr)
            {
                cerr<<"Error!!! In initial state, value "<<fval<<" for variable "<<fname<<" has not been defined!"<<endl;
                return 1;
            }

            if (!v->isValid(ob))
            {
                cerr<<"Error!!!In initial state, value "<<fval<<" is not valid for variable "<<fname<<"!"<<endl;
                return 1;
            }

            Fact f;
            f.setVariable(v);
            f.setValue(ob);


            for (auto it=initial.begin(); it<initial.end();it++)
            {
                if (*((*it).getVariable()) == *v)
                {
                    cerr<<"Error!!! In initial state, duplicate value for "<<fname<<"!"<<endl;
                    return 1;
                }
            }
            initial.push_back(f);
        }
        if (initial.size()!=variables.size())
        {
            cerr<<"Warning!!! Some variables might be uninitialized! The assignments in the initial state are less than the state variables in the problem!"<<endl;
        }
    }

    else
    if (s.find("pre:")!=string::npos || s.find("eff:")!=string::npos)
    {
   //     cout<<"Action"<<endl<<s<<endl;
        stringstream check(s);
        string name;
        getline(check,name,'(');
        Action *b = new Action(name);

//        cout<<"New action "<<name<<endl;

        getline(check,s,')');
        stringstream ss(s);
        string par2;
        while (getline(ss,par2,','))
        {
            stringstream ss2(par2);
            string par;

//            getline(ss2,par,'-');
            getline(ss2,par,':');

            if (! b->addParameter(par))
            {
                cerr<<"Error!!! Action "<<b->getName()<<" uses more than one parameter with name "<<par<<"!"<<endl;
                return 1;
            }

            Parameter *p = b->getParameter(par);

//            getline(ss2,par,'>');

            string test;
            getline(ss2,test,',');

            if (test=="" || test==" ")
            {
                cerr<<"Error!!! Action "<<b->getName()<<" does not reference a domain for parameter "<<p->getName()<<" (Syntax is ... ParN->DomainK)!"<<endl;
                return 1;
            }


            auto it=find(domains.begin(), domains.end(), test);
            if (it == domains.end())
            {
                cerr<<"Error!!! Action "<<b->getName()<<" references undefined domain "<<test<<" for parameter "<<p->getName()<<"!"<<endl;
                return 1;
            }
            p->setDomain(&(*it));
        }

        getline(check,s,';');
        string prec;
        string eff;

        int posprec = s.find("pre:");
        int poseff = s.find("eff:");
        if ( posprec<poseff)
        {
            prec = s.substr(posprec+4, poseff-posprec-4);
            eff=   s.substr(poseff+4);
        }
        else
        {
            eff = s.substr(poseff+4, posprec-poseff-4);
            eff=   s.substr(posprec+4);
        }

//PRECONDITIONS
//cout<<"Prec:"<<prec<<endl;
        stringstream ppAll(prec);
        string sprec;
        while (getline(ppAll,sprec,'&'))
        {
          //  cout<<"pre->"<<sprec<<endl;
            stringstream pp(sprec);

            bool noParam = false;

            if (sprec.find("(")!=string::npos )
                getline(pp,name,'(');
            else
            {
                getline(pp,name,'=');
                noParam=true;
            }



            //getline(pp,name,'(');

        //    cout<<name<<endl;

            bool neg=false;
            if (name[0]=='!')
            {
           //     cout<<"Not"<<endl;
                name.erase(0,1);
             //   cout<<name<<endl;
                neg=true;
            }
//cout<<"Name is "<<name<<endl;
            Precondition *p = new Precondition(name);
            p->setNegative(neg);

            auto it=find(rigids.begin(), rigids.end(), p->getName());
            if (it != rigids.end())
            {
                p->setRigid(true);
            }
            else
            {
                auto it2=find(variables.begin(), variables.end(), name);
                if (it2 != variables.end())
                {
                    p->setVariable(&(*it2));
                    p->setRigid(false);
                }
                else
                {
                    cerr<<"Error!!! In Action "<<b->getName()<<", precondition "<<p->getName()<<" is neither a rigid relation nor a state variable!"<<endl;
                    return 1;

                }
            }

            if (!noParam)
            {
                getline(pp,s,')');
                stringstream ssp(s);
                string par;
                while (getline(ssp,par,','))
                {
                    Parameter *param = b->getParameter(par);
                    if (param==nullptr)
                    {
                        cerr<<"Error!!! In Action "<<b->getName()<<", precondition "<<p->getName()<<" references literal "<<par<<" which is not a parameter of the action!"<<endl;
                        return 1;
                    }
                    if (!p->addParameter(param))
                    {
                        cerr<<"Error!!! In Action "<<b->getName()<<", precondition"<<p->getName()<<" uses the same parameter "<<par<<" twice!"<<endl;
                        return 1;
                    }
                }
            }
            getline(pp,s,'=');
            getline(pp,s,',');

            if (!p->isRigid())
            {
                if (s.length()==0)
                {
                    cerr<<"Error!!! In Action "<<b->getName()<<", precondition "<<p->getName()<<" which is a state variable has no value!"<<endl;
                    return 1;
                }


                if (p->getVariable()->getDomain().isValid(s))
                {
                    auto itO=find(objects.begin(), objects.end(), s);
                    if (itO != objects.end())
                    {
                        p->setValue(*itO);
                    }
                }
                else
                {
                    Parameter *pr = b->getParameter(s);
                    if (pr != nullptr && *(pr->getDomain()) <= p->getVariable()->getDomain())
                    {
                        p->setValue(pr);
                    }
                    else
                    {
                        cerr<<"Error!!! In Action "<<b->getName()<<", value "<<s<<" of precondition "<<p->getName()<<" is incompatible!"<<endl;
                        return 1;
                    }
                }

                //check if s is an object of the correct domain

                //check if s is a parameter with the correct domain



            }


         //   cout<<"prec:"<<p->getName()<<endl;
        //    cout<<p->toString()<<endl;

            b->addPrecondition(p);
        }
        //cout<<"Preconditions ok"<<endl;

//EFFECTS

        stringstream efAll(eff);
        string seff;
        while (getline(efAll,seff,'&'))
        {
            stringstream ee(seff);
      //      cout<<"eff->"<<seff<<endl;


            bool noParam = false;

            if (seff.find("(")!=string::npos )
                getline(ee,name,'(');
            else
            {
                getline(ee,name,'<');
                noParam=true;
            }


            Effect *ef = new Effect(name);

            auto it2=find(variables.begin(), variables.end(), name);
            if (it2 != variables.end())
            {
                ef->setVariable(&(*it2));
                ef->setRigid(false);
            }
            else
            {
                cerr<<"Error!!! In Action "<<b->getName()<<", effect "<<ef->getName()<<" is not a state variable!"<<endl;
                return 1;
            }

            if (!noParam)
            {
                getline(ee,s,')');
                stringstream sse(s);
                string par;
                while (getline(sse,par,','))
                {
                    Parameter *param = b->getParameter(par);
                    if (param==nullptr)
                    {
                        cerr<<"Error!!! In Action "<<b->getName()<<", effect "<<ef->getName()<<" references literal "<<par<<" which is not a parameter of the action!"<<endl;
                        return 1;
                    }
                    if (!ef->addParameter(param))
                    {
                        cerr<<"Error!!! In Action "<<b->getName()<<", effect"<<ef->getName()<<" uses the same parameter "<<par<<" twice!"<<endl;
                        return 1;
                    }
                }
            }
            getline(ee,s,'-');
            getline(ee,s,',');

            if (s.length()==0)
            {
                cerr<<"Error!!! In Action "<<b->getName()<<", effect "<<ef->getName()<<" assigns no value!"<<endl;
                return 1;
            }

            if (ef->getVariable()->getDomain().isValid(s))
            {
                auto itO=find(objects.begin(), objects.end(), s);
                if (itO != objects.end())
                {
                    ef->setValue(*itO);
                }
            }
            else
            {
                Parameter *pr = b->getParameter(s);
                if (pr != nullptr && *(pr->getDomain()) <= ef->getVariable()->getDomain())
                {
                    ef->setValue(pr);
                }
                else
                {
                    cerr<<"Error!!! In Action "<<b->getName()<<", value "<<s<<" of effect "<<ef->getName()<<" is incompatible!"<<endl;
                    return 1;
                }
            }

            b->addEffect(ef);
        }


        auto it=find(actions.begin(), actions.end(), *b);
        if (it != actions.end())
        {
            cerr<<"Error!!! In Action "<<b->getName()<<": an action with the same name already exists!"<<endl;
            return 1;
        }
        actions.push_back(*b);



    //    cout<<"Effects ok"<<endl;

 //       cout<<"prec ="<<prec<<endl;
        //cout<<"eff ="<<eff<<endl;

//        cout<<s<<endl;


//cout<<"Action ok"<<endl;

    //   cout<<"Action "<<b->toString()<<endl;


      //  cout<<"test="<<test<<endl;
    }
    else
//        if (s.find("->")!=string::npos )
        if (s.find(":")!=string::npos )
        {
      //      cout<<"Variable "<<s<<endl;
            stringstream check(s);
            string name;

            bool noParam = false;

            if (s.find("(")!=string::npos )
                getline(check,name,'(');
            else
            {
                getline(check,name,':');
                noParam=true;
            }

           // cout<<s.length()<<" vs "<<name.length()<<endl;




            Variable *b = new Variable(name);

            if (!noParam)
            {
                string par;
                getline(check,par,')');
                auto it=find(objects.begin(), objects.end(), par);
                if (it == objects.end())
                {
                    cerr<<"Error!!! State Variable "<<b->getName()<<" references an undefined object "<<par<<"!"<<endl;
                    return 1;
                }
                b->add(*it);
                string foo;
                getline(check,foo,':');
            }
            string temp,dom;
//            getline(check,temp,'>');
            getline(check,dom,';');

          //  cout<<"domain is "<<dom<<endl;

            auto it2=find(domains.begin(), domains.end(), dom);
            if (it2 == domains.end())
            {
                cerr<<"Error!!! State Variable "<<b->getName()<<" references an undefined domain "<<dom<<"!"<<endl;
                return 1;
            }
         //   cout<<"where?"<<endl;
            b->setDomain(*it2);

           // cout<<"variable:"<<b->toString()<<endl;

            variables.push_back(*b);
        }
        else
            if (s.find("(")!=string::npos || s.find(")")!=string::npos)
            {
        //        cout<<"RIGID"<<endl;
                stringstream check(s);
                string name;
                getline(check,name,'(');
                Rigid *b = new Rigid(name);


                getline(check,s,')');
                stringstream ss(s);
                string par;
                while (getline(ss,par,','))
                {
                    vector<Object>::iterator it=find(objects.begin(), objects.end(), par);
                    if (it == objects.end())
                    {
                        cerr<<"Error!!! Rigid property "<<b->getName()<<" references an undefined object "<<par<<"!"<<endl;
                        return 1;
                    }
                    b->add(*it);
                }
                auto it = find (rigids.begin(), rigids.end(),*b);
                if (it != rigids.end())
                    cout<<"Warning!!! Rigid relation "<<b->toString()<<" already defined!"<<endl;
                rigids.push_back(*b);
            }
            else
                {
             //       cout<<"Domain"<<endl<<s<<endl;
                    stringstream check(s);
                    string name;
                    getline(check,name,'=');
    //                cout<<"name="<<name<<"."<<endl;
                    Domain *b = new Domain(name);


                    auto it = find (domains.begin(), domains.end(),name);
                    if (it != domains.end())
                        cout<<"Warning!!! Domain "<<name<<" already defined!"<<endl;



                    getline(check,s,';');

                    bool add=true;

                    while (s.size()>0)
                    {
                        if (s[0]=='{')
                        {
                            s.erase(0,1);
                            stringstream ss(s);
                            string data;
                            getline(ss,data,'}');
                            getline(ss,s,';');
                            stringstream ss2(data);
                            string datum;
                            Object *o;
                            while (getline(ss2,datum,','))
                            {
                                o= new Object(datum);
                                vector<Object>::iterator it=find(objects.begin(), objects.end(), *o);
                                if (it == objects.end())
                                {
                                    objects.push_back(*o);
                                    it = objects.end()-1;
                                }
                                if (add)
                                    b->add(*it);
                                else
                                    b->del(*it);
                            }
                       //     cout<< "New Domain"<<endl<<b->toString()<<endl;

//                            cout<<"Remaining ="<<s<<endl;
                        }
                        else
                            if (s[0]=='+')
                            {
                                add = true;
                                s.erase(0,1);
                            }
                            else
                            if (s[0]=='-')
                            {
                                add = false;
                                s.erase(0,1);
                            }
                            else
                            {
                                int mend  = strcspn(s.c_str(),"-+;\0\n");

                                string s2 = s.substr(0,mend);
                              //  cout<<s2<<endl;

                                auto it=find(domains.begin(), domains.end(), s2);
                                if (it == domains.end())
                                {
                                    cerr<<"Error!!! Domain "<<s2<<" not found!"<<endl;
                                    return 1;
                                }
                                else
                                {
                                    if (add)
                                        b->add(*it);
                                    else
                                        b->del(*it);
                                }
                                s.erase(0,mend);
                            }
                    }
                    domains.push_back(*b);
             //       cout<<"DOMAIN END"<<endl;
                }

    s=readNext(f);
/*
    getline(f,s,';');

//    removeComments(s);

    s.erase(remove(s.begin(), s.end(), ' '),s.end());
    s.erase(remove(s.begin(), s.end(), '\n'),s.end());
    s.erase(remove(s.begin(), s.end(), '\r'),s.end());
*/
    }

    cout<<endl<<"Problem Analysis:"<<endl;
    cout<<domains.size()<<" domains with "<< objects.size()<<" discrete objects."<<endl;
    cout<<rigids.size()<<" rigid properties and "<<variables.size()<<" state variables."<<endl;
    cout<<actions.size()<<" action templates"<<endl;

  //  cout<<endl<<"SOLVING.......";
//    applyAction(rigids,initial,actions);

    finish= clock();
    double duration = (double)(finish-start)/CLOCKS_PER_SEC;

    cout<<duration<<" secs for parsing."<<endl;
    start = clock();
    long long examined =0;
    long long mem =0;

    FDRSTate *init = new FDRSTate(actions,rigids,initial);
    FDRSTate *goal = new FDRSTate(actions,rigids,goals);

    //FDRSTate *r = BFS2(init,goal,examined,mem);

    cout << "Select algorithm: 1. BFS 2. A*";
        int choice;
    cin >> choice;

    FDRSTate *r ;

    if (choice == 1) {
        r = BFS2(init,goal,examined,mem);
    } else if (choice == 2) {
        r = Astar(init, goal,examined,mem);
    }

    finish= clock();
    duration = (double)(finish-start)/CLOCKS_PER_SEC;

    if (r == nullptr)
    {
        cerr<<"Problem is unsolvable!"<<endl;
        return 1;
    }

    cout<<endl<<"Plan found in "<<duration<<" secs, after examining "<<examined<<" states (memory: "<<mem<<"):"<<endl;
    r->printPath();
/*
    FDRSTate *r2 = DFS(init,goal,examined,mem);
    cout<<endl<<"Plan found after examining "<<examined<<" states (memory: "<<mem<<"):"<<endl;
    r2->printPath();
*/

    return 0;
}
