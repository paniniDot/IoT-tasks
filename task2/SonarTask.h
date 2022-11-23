#ifndef __SONARTASK__
#define __SONARTASK__

#include "Task.h"
#include "Sonar.h"

class SonarTask : public Task {
    private:
        Sonar* sonar;

    public:
        SonarTask(Sonar* sonar);
        void init();
        void tick();
};

#endif