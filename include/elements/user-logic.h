#pragma once

#include <functional>
#include <element.h>

namespace elements {

class UserLogic : public Element {
public:
    typedef std::function<void(Inputs&, Outputs&)> LogicFunction;

    UserLogic(ISimulator &simulator, const std::list<std::string> &input_names,
                     const std::list<std::string> &output_names,
                     LogicFunction logic_function);

    virtual void Resolve() override;

protected:
    LogicFunction _logic_function;
};

}