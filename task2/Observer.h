#ifndef __OBSERVER__
#define __OBSERVER__

class Observer {
    public:
        Observer();
        virtual void update() = 0;
    };

#endif