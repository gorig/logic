#pragma once

#include <functional>
#include <list>
#include <map>
#include <string>
#include <pin.h>

class Simulator;

class Element {
public:
    typedef std::map<std::string, Pin> Inputs;
    typedef std::map<std::string, Pin> Outputs;

    Element();
    Element(ISimulator &simulator, const std::list<std::string> &input_names, const std::list<std::string> &output_names);
    virtual ~Element();

    virtual void Resolve();

    virtual Pin& Input(const std::string &name);
    virtual Pin& Output(const std::string &name);

    virtual const Inputs& inputs() const;
    virtual const Outputs& outputs() const;
    virtual std::list<std::pair<std::reference_wrapper<const std::string>, std::reference_wrapper<const Element>>> descendants() const;

protected:
    Inputs _inputs;
    Outputs _outputs;

    void AddInputs(ISimulator &simulator, const std::list<std::string> &input_names);
    void AddOutputs(ISimulator &simulator, const std::list<std::string> &output_names);
};
