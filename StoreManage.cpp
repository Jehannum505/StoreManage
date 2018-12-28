/*
  StoreManage.cpp - Library for storing and manipulating values.
  Created by Geoff Danielson, 12/25/2018.
  Released into the public domain.
*/

#include "Arduino.h"
#include "StoreManage.h"

float defconv(float f) {
    //this doesn't do anything, but it's better than segfaulting.
    return f;
}

StoreManage::StoreManage() {
    memset(_name, 0,16);
    memset(_siunits, 0, 16);
    memset(_impunits, 0, 16);
    _isSI = true;
    _value = _min = _max = _avg = _samples = 0;
    _convert = &defconv;
}

void StoreManage::setName(const char *name) {
    strncpy(_name, name, 16);
}

void StoreManage::setUnits(const char *units, bool SI) {
    if (SI)
        strncpy(_siunits, units, 16);
    else
        strncpy(_impunits, units, 16);
}

void StoreManage::setConverter(float (*fn)(float)) {
    _convert = fn;
}


void StoreManage::setValue(int value) {
  if (_min > value)
    _min = value;
  if (_max < value)
    _max = value;
  _value = value;
  _avg = ((_avg) * (_samples/(_samples + 1))) + ((value)*(1/(_samples + 1)));
  _samples++;
}

float StoreManage::getValue(bool SI) {
    if ((SI == true && _isSI == true) ||
        (SI == false && _isSI == false))
        return _value;
    return _convert(_value);
}

float StoreManage::getMin(bool SI) {
    if ((SI == true && _isSI == true) ||
        (SI == false && _isSI == false))
        return _min;
    return _convert(_min);
}

float StoreManage::getMax(bool SI) {
    if ((SI == true && _isSI == true) ||
        (SI == false && _isSI == false))
        return _max;
    return _convert(_max);
}

float StoreManage::getAvg(bool SI) {
    if ((SI == true && _isSI == true) ||
        (SI == false && _isSI == false))
        return _avg;
    return _convert(_avg);
}

char * StoreManage::getUnits(bool SI) {
    if (SI)
        return _siunits;
    return _impunits;
}
