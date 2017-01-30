#pragma once

#include <element.h>

namespace elements {

class Logic : public Element {
public:
    Logic(ISimulator &simulator, int inputs_count);
};

}
