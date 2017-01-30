#include <element.h>

Element::Element() {}

Element::Element(ISimulator &simulator, const std::list<std::string> &input_names, const std::list<std::string> &output_names) {
    AddInputs(simulator, input_names);
    AddOutputs(simulator, output_names);
}

Element::~Element() {
}

void Element::Resolve() {
}

Pin& Element::Input(const std::string &name) {
    return _inputs.at(name);
}

Pin& Element::Output(const std::string &name) {
    return _outputs.at(name);
}

const Element::Inputs& Element::inputs() const {
    return _inputs;
}

const Element::Outputs& Element::outputs() const {
    return _outputs;
}

std::list<std::pair<std::reference_wrapper<const std::string>, std::reference_wrapper<const Element>>> Element::descendants() const {
    return std::list<std::pair<std::reference_wrapper<const std::string>, std::reference_wrapper<const Element>>>();
}

void Element::AddInputs(ISimulator &simulator, const std::list<std::string> &input_names) {
    for (const std::string &input_name : input_names) {
        _inputs.emplace(input_name, simulator);
        _inputs.at(input_name).OnChange([this]() {
            Resolve();
        });
    }
}

void Element::AddOutputs(ISimulator &simulator, const std::list<std::string> &output_names) {
    for (const std::string &output_name : output_names) {
        _outputs.emplace(output_name, simulator);
    }
}
