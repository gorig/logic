#include <elements/logic.h>
#include <exception.h>

namespace elements {

Logic::Logic(ISimulator &simulator, int inputs_count) {
    if (inputs_count < 0 || inputs_count > 26) {
        throw Exception("Invalid number of element inputs!");
    }

    std::list<std::string> input_names;
    for (char ch = 'a'; ch < 'a' + inputs_count; ch++) {
        input_names.push_back(std::string(1, ch));
    }

    AddInputs(simulator, input_names);
    AddOutputs(simulator, {"q"});
}

}
