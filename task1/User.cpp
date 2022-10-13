#include "Arduino.h"
#include "User.h"

User::User()
{
    _currentScore = 0;
    _penalties = 0;
}

int User::getPenalties() 
{
    return _penalties;
}

int User::getCurrentScore() 
{
    return _currentScore;
}

void User::addPenalty() 
{
    _penalties++;
}

void User::incrementScore() 
{
    _currentScore++;
}

void User::resetPenalties() 
{
    _penalties = 0;
}

void User::resetScore() 
{
    _currentScore = 0;
}