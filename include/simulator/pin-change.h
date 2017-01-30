#pragma once

#include <isimulator.h>

namespace simulator {

struct PinChange {
    PinChange(std::chrono::nanoseconds time, Pin *pin, LogicValue value);

    std::chrono::nanoseconds time;
    Pin *pin;
    LogicValue value;

    bool operator>(const PinChange &ch) const;
};

}