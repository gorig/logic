#pragma once

#include <element.h>

namespace elements {
namespace generators {

class Clock : public Element {
public:
    Clock(ISimulator &simulator, std::chrono::nanoseconds period)
        : Element(simulator, {}, {"q"}) {
        _outputs.begin()->second.Set(period/2, LogicValue::TRUE);
        _outputs.begin()->second.OnChange([this, period]() {
            _outputs.begin()->second.Set(period/2, !_outputs.begin()->second.value());
        });
    }
};

}
}
