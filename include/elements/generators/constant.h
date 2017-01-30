#pragma once

#include <element.h>

namespace elements {
namespace generators {

using namespace std::chrono_literals;

class Constant : public Element {
public:
    Constant(ISimulator &simulator, LogicValue value)
        : Element(simulator, {}, {"q"}) {
        _outputs.begin()->second.Set(0ns, value);
    }
};

}
}
