#pragma once

#include <cstdint>
#include <string>

class LogicValue {
public:
    enum Value : uint8_t {
        FALSE = 0,
        TRUE = 1,
        FLOATING = 2
    };

    LogicValue(Value value = FLOATING);

    operator Value() const;
    void operator=(Value value);

    operator std::string() const;

    Value operator!() const;
    Value operator&&(const LogicValue &v) const;
    Value operator||(const LogicValue &v) const;

private:
    Value _value;
};
