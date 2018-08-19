#ifndef TIP_INFO_H
#define TIP_INFO_H
#include <iostream>
class TipInfo
{
  private:
    bool info[9] = {false, false, false, false, false, false, false, false, false};
    short numOptions = 9;

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
    TipInfo operator|(const TipInfo &rhs) const;
    bool operator==(const TipInfo &rhs);
    bool operator!=(const TipInfo &rhs);
};

#endif