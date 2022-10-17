/*
  User.h - Library for user statistics handling.
  Created by Eleonora Falconi, Alesja Delja, Riccardo Fiorani, Mattia Panni. October 13, 2022.
  Released into the public domain.
*/
#ifndef USER_H
#define USER_H

#include "Arduino.h"

class User 
{
    public:
        User();
        int getPenalties();
        int getCurrentScore();
        void addPenalty();
        void incrementScore();
        void resetPenalties();
        void resetScore();
    private:
        int _currentScore;
        int _penalties;
};

#endif
