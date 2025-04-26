#include "State.h"
#ifndef search_def
#define search_def

template <typename X>
class Comparator
{
public:
    int operator() (X *p1 , X *p2) const
    {
        return *p1>*p2;
    }
};

template <typename X>
X *Astar(X *initial,X *goal, long long &examined, long long &mem)
{
    priority_queue <X*, vector<X *>, Comparator<X> > agenda;
    unordered_map <X, bool> closed;
    agenda.push(initial);
    examined =0;
    mem=1;
    while (agenda.size()>0)
    {
        if (agenda.size() + closed.size() > mem)
            mem = agenda.size() + closed.size();
        examined++;
        X *s = agenda.top();
        agenda.pop();
        if (*s==*goal)
            return s;
        closed[*s]=true;
        vector<X *> children = s->expand();
        for (unsigned int i=0;i<children.size();i++)
            if (!closed[*children.at(i)])
            {
                children.at(i)->setHvalue(children.at(i)->getDepth()+children.at(i)->heuristic(goal));
                agenda.push(children.at(i));
            }
    }
    return nullptr;
}

template <typename X>
X *BestFS(X *initial,X *goal, long long &examined, long long &mem)
{
    priority_queue <X*, vector<X *>, myComparator > agenda;
    unordered_map <X, bool> closed;
    agenda.push(initial);
    examined = 0;
    mem=1;
    while (agenda.size()>0)
    {
        if (agenda.size() + closed.size() > mem)
            mem = agenda.size() + closed.size();
        examined++;
        X *s = agenda.top();
        agenda.pop();
        if (*s==*goal)
            return s;
        closed[*s]=true;
        vector<X *> children = s->expand();
        for (unsigned int i=0;i<children.size();i++)
            if (!closed[*children.at(i)])
            {
                children.at(i)->setHvalue(children.at(i)->heuristic(goal));
                agenda.push(children.at(i));
            }
    }
    return nullptr;
}
template <typename X>
X *DFS_IDA(X *initial,X *goal, double max_f , double &f, long long &examined, long long &mem)
{
    stack<X *> agenda;
    unordered_map <X, X*> closed;

    f = numeric_limits<double>::infinity();

    agenda.push(initial);

    examined =0;
    mem=1;
    while (agenda.size()>0)
    {
        if (agenda.size() + closed.size() > mem)
            mem = agenda.size() + closed.size();
        examined++;
        X *s = agenda.top();
        agenda.pop();
        if (*s==*goal)
            return s;
        if (s->getHvalue() <= max_f)
        {
            vector<X *> children = s->expand();
            closed[*s]=s;
            for (unsigned i=0;i<children.size();i++)
            {
                children.at(i)->setHvalue(children.at(i)->getDepth() + children.at(i)->heuristic(goal));
                if (closed[*children.at(i)]==nullptr)
                {
                    if (children.at(i)->getHvalue()<=max_f)
                    {
                    agenda.push(children.at(i));
                    }
                    else
                    {
                        if (children.at(i)->getHvalue()<f)
                            f = children.at(i)->getHvalue();
                        delete (children.at(i));
                    }

                }
                else
                    delete (children.at(i));
            }
        }
        else
        {
            if (s->getHvalue()<f)
                f = s->getHvalue();
            if (s->getDepth()>0)
                delete(s);
        }
        bool removed = true;
        while (removed)
        {
            removed = false;
            auto i=closed.begin();
            while (i!= closed.end())
            {
                if (i->second!=nullptr && i->second->getNoChildren()==0)
                {
                    if (i->second->getDepth()>0)
                        delete (i->second);
                    closed[i->first]=nullptr;
                    removed = true;
                }
                    else
                        i++;
            }
        }

    }
    return nullptr;
}
template <typename X>
X *DFS_BB(X *initial,X *goal, double max_f , double &f, long long &examined, long long &mem)
{
    stack<X *> agenda;
    unordered_map <X, X*> closed;

    f = numeric_limits<double>::infinity();

    agenda.push(initial);

    examined =0;
    mem=1;
    while (agenda.size()>0)
    {
        if (agenda.size() + closed.size() > mem)
            mem = agenda.size() + closed.size();
        examined++;
        X *s = agenda.top();
        agenda.pop();
        if (*s==*goal)
            return s;
        if (s->getHvalue() < max_f)
        {
            vector<X *> children = s->expand();
            closed[*s]=s;
            for (unsigned i=0;i<children.size();i++)
            {
                children.at(i)->setHvalue(children.at(i)->getDepth() + children.at(i)->heuristic(goal));
                if (closed[*children.at(i)]==nullptr)
                {
                    if (children.at(i)->getHvalue()<max_f)
                    {
                    agenda.push(children.at(i));
                    }
                    else
                        delete (children.at(i));

                }
                else
                    delete (children.at(i));
            }
        }
        else
        {
            if (s->getHvalue()<f)
                f = s->getHvalue();
            if (s->getDepth()>0)
                delete(s);
        }
        bool removed = true;
        while (removed)
        {
            removed = false;
            auto i=closed.begin();
            while (i!= closed.end())
            {
                if (i->second!=nullptr && i->second->getNoChildren()==0)
                {
                    if (i->second->getDepth()>0)
                        delete (i->second);
                    closed[i->first]=nullptr;
                    removed = true;
                }
                    else
                        i++;
            }
        }

    }
    return nullptr;
}

template <typename X>
X *IDA(X *initial,X *goal, long long &examined, long long &mem)
{
    double c=0,f;

 //   cout<<"New value is "<<c<<endl;
    initial->setHvalue(initial->getDepth()+initial->heuristic(goal));
    long long ex, m;

    X *r = DFS_IDA(initial,goal,c,f,ex,m);
    examined=ex;
    mem=m;

    while (r==nullptr)
    {
        c=f;
     //   cout<<"New value is "<<c<<endl;
        initial->setHvalue(initial->getDepth()+initial->heuristic(goal));
        r = DFS_IDA(initial,goal,c,f,ex,m);
        examined+=ex;
        mem = mem>m?mem:m;
    }
    return r;
}
template <typename X>
X *BFS(X *initial,X *goal, long long &examined, long long &mem)
{
    queue<X *> agenda;
    unordered_map <X, bool> closed;
    agenda.push(initial);
    examined=0;
    mem=1;
    while (agenda.size()>0)
    {
        if (agenda.size() + closed.size() > mem)
            mem = agenda.size() + closed.size();
        examined++;
        X *s = agenda.front();
        agenda.pop();
        if (*s==*goal)
            return s;
        closed[*s]=true;
        vector<X *> children =s->expand();
        for (unsigned int i=0;i<children.size();i++)
            if (!closed[*children.at(i)])
                agenda.push(children.at(i));
    }
    return nullptr;
}

bool operator==(const pair<const FDRSTate, bool> mypair, const FDRSTate mystate)
{
    return (mypair.first == mystate);
}


template <typename X>
X *BFS2(X *initial,X *goal, long long &examined, long long &mem)
{
    queue<X *> agenda;
    unordered_map <X, bool> closed;
    agenda.push(initial);
    examined=0;
    mem=1;
    while (agenda.size()>0)
    {
        if (agenda.size() + closed.size() > mem)
            mem = agenda.size() + closed.size();
        X *s = agenda.front();
        agenda.pop();

        if (closed.find(*s)==closed.end())
//        if (!closed[*s])
        {
//            auto fgood = closed.find(*s);
  //          if (fgood != closed.end())
    //            cout<<"Not in close list"<<endl;
     //       else
      //          cout<<"In close list"<<endl;
        //    auto fml = find(closed.begin(), closed.end(), *s);
//            if (fml != closed.end())
  //          {
    //            cout<<s->toString()<< " vs "<< (*fml).first.toString()<<endl;
      //          cout<<"Don't agree "<<s->getKey()<< " vs "<<(*fml).first.getKey() <<endl;
        //        cout<<closed[*s]<<endl;
          //  }

            examined++;
            if (*s==*goal)
                return s;
            pair<X,bool> k (*s,true);
            closed.insert(k);
         //   closed[*s]=true;
            vector<X *> children =s->expand();
            for (unsigned int i=0;i<children.size();i++)
                if (closed.find(*children[i])==closed.end())
//                if (!closed[*children.at(i)])
                    agenda.push(children.at(i));
        }

    }
    return nullptr;
}
template <typename X>
X *BFS3(X *initial,X *goal, long long &examined, long long &mem)
{
    queue<X *> agenda;
    vector <X> closed;
    //unordered_map <X, bool> closed;
    agenda.push(initial);
    examined=0;
    mem=1;
    while (agenda.size()>0)
    {
        if (agenda.size() + closed.size() > mem)
            mem = agenda.size() + closed.size();
        X *s = agenda.front();
        agenda.pop();
//        if (!closed[*s])
        auto inc = find(closed.begin(), closed.end(), *s);
        if (inc == closed.end())
        {
            examined++;
            if (*s==*goal)
                return s;
//            closed[*s]=true;
            closed.push_back(*s);
            vector<X *> children =s->expand();
            for (unsigned int i=0;i<children.size();i++)
            {
                auto inc = find(closed.begin(), closed.end(), *children[i]);
                if (inc == closed.end())
//                if (!closed[*children.at(i)])
                    agenda.push(children.at(i));

            }
        }

    }
    return nullptr;
}

template <typename X>
X *DFS(X *initial,X *goal, long long &examined, long long &mem)
{
    stack<X *> agenda;
    unordered_map <X, bool> closed;
    agenda.push(initial);
    examined=0;
    mem=1;
    while (agenda.size()>0)
    {
        if (agenda.size() + closed.size() > mem)
            mem = agenda.size() + closed.size();
        examined++;
        X *s = agenda.top();
        agenda.pop();
        if (*s==*goal)
            return s;
        vector<X *> children = s->expand();
        closed[*s]=true;
        for (unsigned int i=0;i<children.size();i++)
            if (!closed[*children.at(i)])
                agenda.push(children.at(i));
            else
                delete (children.at(i));

    }
    return nullptr;
}
template <typename X>
X *DFS_BB(X *initial,X *goal, long long &examined, long long &mem)
{
    double c = 22;//numeric_limits<double>::infinity();
    double f;
    X *p;
    initial->setHvalue(initial->getDepth()+initial->heuristic(goal));
    long long ex,m;

    X *r = DFS_BB(initial,goal,c,f, ex, m);

    examined = ex;
    mem = m;

    while (r!=nullptr)
    {
        c = r->getDepth();
        p = r;
        r = DFS_BB(initial,goal,c,f,ex,m);
        examined +=ex;
        mem = mem>m?mem:m;
    }
    return p;
}
template <typename X>
X *DFS(X *initial,X *goal, unsigned int max_depth, long long &examined, long long &mem)
{
    stack<X *> agenda;
    unordered_map <X, X*> closed;
    agenda.push(initial);
    examined =0;
    mem=1;
    while (agenda.size()>0)
    {
        if (agenda.size() + closed.size() > mem)
            mem = agenda.size() + closed.size();
        examined++;
        X *s = agenda.top();
        agenda.pop();
        if (*s==*goal)
            return s;
        if (s->getDepth()<max_depth)
        {
            vector<X *> children = s->expand();
            closed[*s]=s;
            for (int i=0;i<children.size();i++)
                if (closed[*children.at(i)]==nullptr)
                    agenda.push(children.at(i));
                else
                    delete (children.at(i));
        }
        else
            delete(s);

        bool removed = true;
        while (removed)
        {
            removed = false;
            auto i=closed.begin();
            while (i!= closed.end())
            {
                if (i->second!=nullptr && i->second->getNoChildren()==0)
                {
                    if (i->second->getDepth()>0)
                        delete (i->second);
                    closed[i->first]=nullptr;
                    removed = true;
                }
                    else
                        i++;
            }
        }

    }
    return nullptr;
}
template <typename X>
X *ID_DFS(X *initial,X *goal, unsigned int depth, unsigned int increment, long long &examined, long long &mem)
{
    long long m,ex;
    X *sol = DFS(initial,goal,depth,ex,m);
    examined =ex;
    mem = m;
    while (sol==nullptr)
    {
        depth+=increment;
//        cout<<"New depth: "<<depth<<endl;
        sol = DFS(initial,goal,depth,ex,m);
        examined+=ex;
        mem=mem>m?mem:m;
    }
    return sol;
}


#endif
