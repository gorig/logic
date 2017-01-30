#include <elements/user-logic.h>

namespace elements {

UserLogic::UserLogic(ISimulator &simulator, const std::list<std::string> &input_names,
                                   const std::list<std::string> &output_names,
                                   LogicFunction logic_function)
    : Element(simulator, input_names, output_names), _logic_function(logic_function) {}

void UserLogic::Resolve() {
    _logic_function(_inputs, _outputs);
}

}