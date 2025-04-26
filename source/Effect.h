#ifndef EFFECT_H
#define EFFECT_H

#include "Precondition.h"


class Effect : public Precondition
{
    public:
        Effect(string);
        string toString();

    protected:

    private:
};

#endif // EFFECT_H
