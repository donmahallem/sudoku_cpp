#include <iostream>
#include <assert.h>
#include "tip_info.h"

TipInfo::TipInfo()
{
}
TipInfo::~TipInfo()
{
}

bool TipInfo::get(const short value) const
{
    assert(value >= 1 && value <= 9);
    return this->info[value - 1];
};

void TipInfo::set(const short value, const bool state)
{
    //std::cout << "val set" << value << std::endl;
    assert(value >= 1 && value <= 9);
    this->info[value - 1] = state ? true : false;
    this->numOptions += state ? -1 : 1;
};
void TipInfo::setAll(bool state)
{
    for (short i = 0; i < 9; i++)
    {
        this->info[i] = state;
    }
    this->numOptions = state ? 0 : 9;
};
void TipInfo::reset()
{
    this->setAll(false);
    this->numOptions = 9;
};

short TipInfo::getNumOptions() const
{
    return this->numOptions;
}
bool TipInfo::operator==(const TipInfo &rhs)
{
    for (short i = 0; i < 9; i++)
    {
        if (this->info[i] != rhs.info[i])
        {
            return false;
        }
    }
    return true;
}
bool TipInfo::operator!=(const TipInfo &rhs)
{
    for (short i = 0; i < 9; i++)
    {
        if (this->info[i] != rhs.info[i])
        {
            return true;
        }
    }
    return false;
}
TipInfo TipInfo::operator|(const TipInfo &rhs) const
{
    TipInfo out;
    out.numOptions = 9;
    for (short i = 0; i < 9; i++)
    {
        if (this->info[i] | rhs.info[i])
        {
            out.info[i] = true;
            out.numOptions -= 1;
        }
        else
        {
            out.info[i] = false;
        }
    }
    return out;
}
std::ostream &operator<<(std::ostream &out, const TipInfo &info)
{
    out << "TipInfo(";
    bool foundOne = false;
    for (short i = 1; i <= 9; i++)
    {
        if (!info.get(i))
        {
            if (foundOne)
            {
                out << ",";
            }
            out << std::to_string(i);
            foundOne = true;
        }
    }
    out << ")";
    return out;
}