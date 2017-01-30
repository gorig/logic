#pragma once

#include <simulator/simulator.h>
#include <json11.hpp>

namespace simulator {

class Loader {
public:
    Loader(Simulator &simulator);

    void Load(const std::string &filename);

private:
    Simulator &_simulator;

    std::unique_ptr<Element> LoadElementFromFile(const std::string &filename);
    std::unique_ptr<Element> LoadComposition(const json11::Json::object &data);

    static json11::Json LoadJson(const std::string &filename);
    static std::string LoadFile(const std::string &filename);
};

}