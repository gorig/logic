#pragma once

#include <element.h>

namespace elements {
namespace logic {

using namespace std::chrono_literals;

class Not : public Element {
public:
    Not(ISimulator &simulator)
        : Element(simulator, {"a"}, {"q"}) {}

    virtual void Resolve() override {
        switch (_inputs.begin()->second.value()) {
            case LogicValue::FALSE:
                _outputs.begin()->second.Set(1ns, LogicValue::TRUE);
                break;
            case LogicValue::TRUE:
                _outputs.begin()->second.Set(1ns, LogicValue::FALSE);
                break;
            case LogicValue::FLOATING:
                _outputs.begin()->second.Set(1ns, LogicValue::FLOATING);
                break;
        }
    }
};

}
}
