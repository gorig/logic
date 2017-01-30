#include <elements/composition.h>
#include <exception.h>

using namespace std::chrono_literals;

namespace elements {

Composition::Composition(ISimulator &simulator, const std::list<std::string> &input_names,
                                       const std::list<std::string> &output_names)
    : Element(simulator, input_names, output_names) {}

void Composition::AddElement(const std::string &name, std::unique_ptr<Element> &&element) {
    _elements[name] = std::move(element);
}

void Composition::AddWire(const std::string &source_element, const std::string &source_pin,
                                 const std::string &target_element, const std::string &target_pin) {
    try {
        Pin &source = _elements.at(source_element)->Output(source_pin);
        Pin &target = _elements.at(target_element)->Input(target_pin);

        source.OnChange([this, &source, &target]() {
            target.Set(1ns, source.value());
        });
    } catch (std::out_of_range e) {
        //TODO: Create exception hierarchy
        throw Exception("Unable to create wire " + source_element + "." + source_pin + "->" + target_element + "." + target_pin
            + "!");
    }
}

std::list<std::pair<std::reference_wrapper<const std::string>,
                    std::reference_wrapper<const Element>>> Composition::descendants() const {
    std::list<std::pair<std::reference_wrapper<const std::string>, std::reference_wrapper<const Element>>> descendants;
    for (const auto &element : _elements) {
        descendants.emplace_back(element.first, *element.second);
    }
    return descendants;
}

}