#include <simulator/loader.h>

#include <cstdio>
#include <elements/composition.h>
#include <elements/generators/clock.h>
#include <elements/generators/constant.h>
#include <elements/logic/and.h>
#include <elements/logic/nand.h>
#include <elements/logic/nor.h>
#include <elements/logic/not.h>
#include <elements/logic/or.h>
#include <exception.h>

using namespace std::chrono_literals;

namespace simulator {

Loader::Loader(Simulator &simulator) : _simulator(simulator) {}

void Loader::Load(const std::string &filename) {
    _simulator.SetRootElement(LoadElementFromFile(filename));
}

//TODO: Better error checking
std::unique_ptr<Element> Loader::LoadElementFromFile(const std::string &filename) {
    json11::Json json(LoadJson(filename));

    if (!json.is_object()) {
        throw Exception("Element load error: Object expected!");
    }

    try {
        const std::string &type = json.object_items().at("type").string_value();
        const auto &data = json.object_items();

        if (type == "composition") {
            return LoadComposition(data);
        } else if (type == "generators.constant") {
            bool value = data.at("value").bool_value();
            return std::make_unique<elements::generators::Constant>(_simulator, value?LogicValue::TRUE:LogicValue::FALSE);
        } else if (type == "generators.clock") {
            int64_t period = int64_t(data.at("period").number_value());
            if (period < 2.0) {
                throw Exception("Clock period must be greater than 2ns!");
            }
            return std::make_unique<elements::generators::Clock>(_simulator, period*1ns);
        } else if (type == "logic.and") {
            int inputs_count = data.at("inputs").int_value();
            return std::make_unique<elements::logic::And>(_simulator, inputs_count);
        } else if (type == "logic.nand") {
            int inputs_count = data.at("inputs").int_value();
            return std::make_unique<elements::logic::Nand>(_simulator, inputs_count);
        } else if (type == "logic.nor") {
            int inputs_count = data.at("inputs").int_value();
            return std::make_unique<elements::logic::Nor>(_simulator, inputs_count);
        } else if (type == "logic.not") {
            return std::make_unique<elements::logic::Not>(_simulator);
        } else if (type == "logic.or") {
            int inputs_count = data.at("inputs").int_value();
            return std::make_unique<elements::logic::Or>(_simulator, inputs_count);
        } else {
            throw Exception("Element load error: The element type has not been specified!");
        }

    } catch (std::out_of_range e) {
        throw Exception("Element load error: The element type has not been specified!");
    }
}

//TODO: Better error checking
std::unique_ptr<Element> Loader::LoadComposition(const json11::Json::object &data) {
    std::list<std::string> input_names;
    std::list<std::string> output_names;

    for (const auto &input : data.at("inputs").array_items()) {
        input_names.push_back(input.string_value());
    }
    for (const auto &output : data.at("outputs").array_items()) {
        output_names.push_back(output.string_value());
    }

    auto element = std::unique_ptr<elements::Composition>(new elements::Composition(_simulator, input_names, output_names));

    for (const auto &descendant : data.at("elements").array_items()) {
        const auto &descendant_data = descendant.object_items();
        const std::string &name = descendant_data.at("name").string_value();
        const std::string &filename = descendant_data.at("file").string_value();
        element->AddElement(name, LoadElementFromFile(filename));
    }

    for (const auto &wire : data.at("wires").array_items()) {
        const auto &wire_data = wire.object_items();
        const auto &from = wire_data.at("from").object_items();
        const auto &to = wire_data.at("to").object_items();
        element->AddWire(from.at("element").string_value(), from.at("pin").string_value(),
                         to.at("element").string_value(), to.at("pin").string_value());
    }

    return element;
}

json11::Json Loader::LoadJson(const std::string &filename) {
    std::string file_content(LoadFile(filename));
    std::string error;

    json11::Json json(json11::Json::parse(file_content, error, json11::JsonParse::COMMENTS));
    if (!error.empty()) {
        throw Exception("JSON parse error: " + error);
    }

    return json;
}

std::string Loader::LoadFile(const std::string &filename) {
    FILE *fr = fopen(filename.c_str(), "r");
    if (!fr) {
        throw Exception("Unable to load file " + filename + "!");
    }

    std::string file_content;
    char buffer[512];
    while (fgets(buffer, sizeof(buffer), fr) != nullptr) {
        file_content += buffer;
    }

    fclose(fr);
    return file_content;
}

}