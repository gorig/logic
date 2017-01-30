#pragma once

#include <memory>
#include <vector>
#include <element.h>

namespace elements {

class Composition : public Element {
public:
    Composition(ISimulator &simulator,
                       const std::list<std::string> &input_names,
                       const std::list<std::string> &output_names);

    void AddElement(const std::string &name, std::unique_ptr<Element> &&element);
    void AddWire(const std::string &source_element, const std::string &source_pin,
                 const std::string &target_element, const std::string &target_pin);

    virtual std::list<std::pair<std::reference_wrapper<const std::string>,
                                std::reference_wrapper<const Element>>> descendants() const override;

protected:
    std::map<std::string, std::unique_ptr<Element>> _elements;
};

}