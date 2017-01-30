#include <simulator/simulator.h>

#include <pin.h>
#include <exception.h>

namespace simulator {

Simulator::Simulator() : _simulation_time(0) {}

void Simulator::SetRootElement(std::unique_ptr<Element> &&element) {
    _root_element = std::move(element);
}

void Simulator::Run(std::chrono::nanoseconds time) {
    std::chrono::nanoseconds finish_time = _simulation_time + time;
    while (!_pending_changes.empty() && _pending_changes.top().time <= finish_time) {
        Step();
    }
}

void Simulator::Step() {
    if (_pending_changes.empty()) {
        return;
    }

    //NOTE: Copying value to be sure nobody alter the top before removing.
    PinChange change(_pending_changes.top());
    _pending_changes.pop();

    _simulation_time = change.time;
    change.pin->SetNow(change.value);
}

void Simulator::Terminate() {
    //Clear pending changes queue
    _pending_changes = std::priority_queue<PinChange, std::vector<PinChange>, std::greater<PinChange>>();
}

void Simulator::SetPinValue(std::chrono::nanoseconds delay, Pin &pin, LogicValue value) {
    _pending_changes.push(PinChange(_simulation_time + delay, &pin, value));
}

void Simulator::UnregisterPin(Pin &pin) {
    //TODO: Implement
    if (!_pending_changes.empty()) {
        throw Exception("Trying to unregister pin during simulation!\n");
    }
}

std::chrono::nanoseconds Simulator::simulation_time() const {
    return _simulation_time;
}

static json11::Json GetPinResult(const Pin &pin) {
    json11::Json::array result;
    for (const auto &value : pin.history_values()) {
        result.push_back(json11::Json::array {double(value.first.count()), std::string(value.second)});
    }
    return result;
}

static void GetResult(json11::Json::object &result, const Element &element, const std::string &prefix) {
    for (const auto &descendant : element.descendants()) {
        GetResult(result, descendant.second, prefix + "." + descendant.first.get());
    }
    for (const auto &input : element.inputs()) {
        result[prefix + ".inputs." + input.first] = GetPinResult(input.second);
    }
    for (const auto &output : element.outputs()) {
        result[prefix + ".outputs." + output.first] = GetPinResult(output.second);
    }
}

json11::Json Simulator::GetResult() {
    if (_root_element == nullptr) {
        throw Exception("Root element not selected!");
    }

    json11::Json::object result;
    simulator::GetResult(result, *_root_element, "root");
    return result;
}

}