#ifndef __SUBJECT__
#define __SUBJECT__

#include "Observer.h"

template <typename T>

#define INITIAL_OBSERVERS 10

class Subject {
    private:
        Observer* observers[INITIAL_OBSERVERS];
        int nObservers;

    public:
        virtual void attach(Observer* o) = 0;
        virtual void detach(Observer* o) = 0;
        virtual void notify() = 0;
};

#endif