#ifndef __STOREMANAGE_H__
#define __STOREMANAGE_H__

#include "Arduino.h"

class StoreManage {
  public:
    StoreManage();
    void setValue(int value);
    void setName(const char *name);
    void setUnits(const char *units, bool SI);
    void setSI(bool SI) { _isSI = SI; }
    void setConverter(float (*fn)(float));
    float getValue(bool SI);
    float getMin(bool SI);
    float getMax(bool SI);
    float getAvg(bool SI);
    char *getName() { return _name; }
    char *getUnits(bool SI);
private:
    char _name[16], _siunits[16], _impunits[16];
    float _value, _min, _max, _avg;
    size_t _samples;
    bool _isSI;
    float (*_convert)(float);
};

#endif
