#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <sstream>
#include <iostream>

#ifndef state_def
#define state_def
using namespace std;

class State
{
    protected:
        State *father;
        vector<State *> children;
        int depth=0;
        double Hvalue;
        string name;
    public:
        State();
        ~State();
        int getDepth();
        void setDepth(int);
        void setHvalue(double);
        double getHvalue();
        State *getFather();
        void addChild(State *);
        void removeChild(State *);
        int getNoChildren();
        vector<State *> getChildren(){return children;}
        string getPath();
        virtual double heuristic (State *goal) {return 0;};
        bool operator>(State b){return getHvalue()>b.getHvalue();}


};
class myComparator
{
public:
    int operator() (State *p1 , State *p2) const
    {
        return p1->getHvalue()>p2->getHvalue();
    }
};

#endif // state_def
