#include "GroundedAction.h"

using namespace std;


Fact GroundedAction::getEffect(int i)
{
    Fact f;
    Effect *e = a->getEffect(i);

    if (e->isValueObject())
    {
        Object *no = new Object(e->getValue().getDescription());
        f.setValue(no);
    }
    else
    {
        int kl = a->getParameterPosition(e->getValueP()->getName());
        Object *no = new Object(mypar[kl].getValue().getDescription());
        f.setValue(no);
    }

    Variable *v = new Variable(e->getName());

    vector<Parameter *> &pp = e->getParameterVector();

//    cout<<"Parames in parame vector: "<<e->getParameterVector().size()<<endl;

    for (int k=0;k<pp.size();k++)
    {
        int kp = a->getParameterPosition(pp[k]->getName());
        v->add(Object(mypar[kp].getValue().getDescription()));
    }
    f.setVariable(v);

    return f;
}
string GroundedAction::toString()
{
    string s;
    s = a->getName();

    if (a->getParameterCount()>0)
    {
        s+="(";
        for (int i=0;i<a->getParameterCount()-1;i++)
            s+=mypar[i].getValue().getDescription()+",";
        s+=mypar[a->getParameterCount()-1].getValue().getDescription()+")";
    }

    return s;
}
