#ifndef __EVENT__
#define __EVENT__

template <typename T>

class Event {

    private:
        T* eventArgs;

    public:
        Event(T* eventArgs) {
            this->eventArgs = eventArgs;
        }

        T* getEventArgs() {
            return eventArgs;
        }

};

#endif