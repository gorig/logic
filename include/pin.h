#pragma once

#include <chrono>
#include <functional>
#include <list>
#include <vector>
#include <isimulator.h>
#include <logic-value.h>

class Pin {
public:
    Pin(ISimulator &simulator);
    ~Pin();

    void Set(std::chrono::nanoseconds delay, LogicValue value);
    void SetNow(LogicValue value);

    void OnChange(std::function<void()> callback);

    const LogicValue& value() const;
    const std::list<std::pair<std::chrono::nanoseconds, LogicValue>>& history_values() const;

private:
    LogicValue _value;
    ISimulator &_simulator;
    std::vector<std::function<void()>> _on_change_callbacks;
    std::list<std::pair<std::chrono::nanoseconds, LogicValue>> _history_values;
};
