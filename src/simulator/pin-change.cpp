#include <simulator/pin-change.h>

namespace simulator {

PinChange::PinChange(std::chrono::nanoseconds time, Pin *pin, LogicValue value)
    : time(time), pin(pin), value(value) {}

bool PinChange::operator>(const PinChange &ch) const {
    return time > ch.time;
}

}