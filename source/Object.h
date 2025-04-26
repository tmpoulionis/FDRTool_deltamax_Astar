#ifndef OBJECT_H
#define OBJECT_H
#include <string>

using namespace std;
class Object
{
    public:
        Object(){}
        Object(string);

        bool operator == (const string s)
        {
            return s==description;
        }

        bool operator == (const Object o)
        {
            return o.description==description;
        }
        bool operator != (const Object o)
        {
            return o.description!=description;
        }

        string getDescription() const {return description;}

    private:
        string description;
};


#endif // OBJECT_H
