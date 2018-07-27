#include <iostream>
#include <assert.h>
#include "tip_info.h"

TipInfo::TipInfo()
{
    this->reset();
}
TipInfo::~TipInfo()
{
    //delete this->field;
    //std::cout << "destruct";
}

bool TipInfo::get(short value) const
{
    assert(value >= 1 || value <= 9);
    return this->info[value - 1];
};

void TipInfo::set(short value, bool state)
{
    //std::cout << "val set" << value << std::endl;
    assert(value >= 1 && value <= 9);
    this->info[value - 1] = state;
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
    for (short i = 1; i <= 9; i++)
    {
        if (this->get(i) != rhs.get(i))
        {
            return false;
        }
    }
    return true;
}

TipInfo &operator|(const TipInfo &lhs, const TipInfo &rhs)
{
    TipInfo *out = new TipInfo();
    int opts = 9;
    for (short i = 1; i <= 9; i++)
    {
        out->set(i, lhs.get(i) | rhs.get(i));
        opts -= (lhs.get(i) | rhs.get(i));
    }
    out->numOptions = opts;
    return *out;
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