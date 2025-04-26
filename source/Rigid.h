#ifndef RIGID_H
#define RIGID_H
#include <string>
#include <vector>
#include "Object.h"
#include <iostream>
using namespace std;

using namespace std;

class Rigid
{
    public:
        Rigid(string);

        string getName() const
        {
            return name;
        }
        void add (const Object &);
        string toString() const;
        bool operator == (const string &s)
        {
//            cout<<"Comparing "<<s<< " and "<< name;
            if (name==s)
            {
  //              cout<<"Yes"<<endl;
                return true;
            }
    //        cout<<"No"<<endl;
            return false;
        }

        bool operator == (const Rigid &o)
        {
            if (name!=o.name)
                return false;

            if (parameters.size() != o.parameters.size())
                return false;

            for (int i=0;i<parameters.size();i++)
                    if (parameters[i]!=o.parameters[i])
                        return false;
            return true;
        }
        Object getParameter(int i) {return parameters[i];}
        int getParameters (){return parameters.size();}
        void copyParameters (const vector <Object> &p) {parameters=p;}

    protected:
        string name;
        vector <Object > parameters;
};

#endif // RIGID_H
