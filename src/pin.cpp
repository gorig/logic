#include <pin.h>

using namespace std::chrono_literals;

Pin::Pin(ISimulator &simulator) : _simulator(simulator) {
    _history_values.emplace_back(0ns, LogicValue::FLOATING);
}

Pin::~Pin() {
    _simulator.UnregisterPin(*this);
}

void Pin::Set(std::chrono::nanoseconds delay, LogicValue value) {
    _simulator.SetPinValue(delay, *this, value);
}

void Pin::SetNow(LogicValue value) {
    if (value != _value) {
        _value = value;
        _history_values.emplace_back(_simulator.simulation_time(), value);
        for (auto &callback : _on_change_callbacks) {
            callback();
        }
    }
}

void Pin::OnChange(std::function<void()> callback) {
    _on_change_callbacks.push_back(callback);
}

const LogicValue &Pin::value() const {
    return _value;
}

const std::list<std::pair<std::chrono::nanoseconds, LogicValue>>& Pin::history_values() const {
    return _history_values;
}