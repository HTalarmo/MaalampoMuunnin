#ifndef UTILS
#define UTILS

#include <iostream>

struct Time
{

    int d;
    int m;
    int y;

    int h;
    int min;

    Time()
    {

    }

    std::string toString() const
    {
        std::string result;
        result = std::to_string(d) + "." + std::to_string(m) + "." + std::to_string(y);
        result += " " + std::to_string(h) + ":" + std::to_string(min);
        return result;
    }

    bool operator<(const Time& rhs) const
    {
        if(y < rhs.y) return true;
        else if (y > rhs.y) return false;

        if(m < rhs.m) return true;
        else if (m > rhs.m) return false;

        if(d < rhs.d) return true;
        else if (d > rhs.d) return false;

        if(h < rhs.h) return true;
        else if(h > rhs.h) return true;

        if(min < rhs.min) return true;
        else return false;
    }

    bool operator<=(const Time& rhs)
    {
        if(y < rhs.y) return true;
        else if (y > rhs.y) return false;

        if(m < rhs.m) return true;
        else if (m > rhs.m) return false;

        if(d < rhs.d) return true;
        else if (d > rhs.d) return false;

        if(h < rhs.h) return true;
        else if(h > rhs.h) return true;

        if(min <= rhs.min) return true;
        else return false;
    }

    bool operator==(const Time& rhs)
    {
        if(y != rhs.y) return false;
        if(m != rhs.m) return false;
        if(d != rhs.d) return false;
        if(h != rhs.h) return false;
        if(min != rhs.min) return false;
        return true;
    }


};

#endif // UTILS

