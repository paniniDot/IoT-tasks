#ifndef __STATE__
#define __STATE__

enum WaterState
{
    NORMAL,
    PRE_ALARM,
    ALARM
};

enum PeopleState
{
    PRESENT_DAY,
    NOT_PRESENT_DAY,
    PRESENT_NIGHT,
    NOT_PRESENT_NIGHT
};

#endif