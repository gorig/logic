#pragma once

#include <chrono>
#include <functional>
#include <map>
#include <queue>
#include <json11.hpp>
#include <element.h>
#include <isimulator.h>
#include <simulator/pin-change.h>

namespace simulator {

class Simulator : public ISimulator {
public:
    Simulator();

    void SetRootElement(std::unique_ptr<Element> &&element);
    void Run(std::chrono::nanoseconds time);
    void Step();
    void Terminate();

    virtual void SetPinValue(std::chrono::nanoseconds delay, Pin &pin, LogicValue value) override;
    virtual void UnregisterPin(Pin &pin);
    virtual std::chrono::nanoseconds simulation_time() const override;

    json11::Json GetResult();

private:
    std::unique_ptr<Element> _root_element;
    std::chrono::nanoseconds _simulation_time;
    std::priority_queue<PinChange, std::vector<PinChange>, std::greater<PinChange>> _pending_changes;
};

}
