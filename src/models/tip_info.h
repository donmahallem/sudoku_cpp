#ifndef TIP_INFO_H
#define TIP_INFO_H
#include <iostream>
class TipInfo
{
  private:
    bool info[9];
    short numOptions;

  public:
    TipInfo();
    ~TipInfo();
    void set(short value, bool state);
    bool get(short value) const;
    void setAll(bool state);
    void reset();
    short getNumOptions() const;

  public:
    friend std::ostream &operator<<(std::ostream &out, const TipInfo &tipInfo);
    friend TipInfo &operator|(const TipInfo &lhs, const TipInfo &rhs);
    bool operator==(const TipInfo &rhs);
};

#endif