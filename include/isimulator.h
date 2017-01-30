#pragma once

#include <chrono>
#include <logic-value.h>

class Pin;

class ISimulator {
public:
    virtual void SetPinValue(std::chrono::nanoseconds delay, Pin &pin, LogicValue value) = 0;
    virtual void UnregisterPin(Pin &pin) = 0;

    virtual std::chrono::nanoseconds simulation_time() const = 0;
};