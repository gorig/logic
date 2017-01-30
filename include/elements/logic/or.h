#pragma once

#include <elements/logic.h>

namespace elements {
namespace logic {

using namespace std::chrono_literals;

class Or : public Logic {
public:
    Or(ISimulator &simulator, int input_count)
        : Logic(simulator, input_count) {}

    virtual void Resolve() override {
        LogicValue result = LogicValue::TRUE;
        for (auto &input : _inputs) {
            result = result || input.second.value();
        }
        _outputs.begin()->second.Set(1ns, result);
    }
};

}
}
