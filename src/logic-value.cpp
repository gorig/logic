#include <logic-value.h>

LogicValue::LogicValue(Value value)
        : _value(value) {}

LogicValue::operator Value() const {
    return _value;
}

void LogicValue::operator=(Value value) {
    _value = value;
}

LogicValue::operator std::string() const {
    switch (_value) {
        case FALSE: return "0";
        case TRUE: return "1";
        case FLOATING: return "Z";
    }
    return "Z";
}

LogicValue::Value LogicValue::operator!() const {
    if (_value == FLOATING) {
        return FLOATING;
    }
    return (_value==TRUE)?FALSE:TRUE;
}

LogicValue::Value LogicValue::operator&&(const LogicValue &v) const {
    if (_value == FLOATING || v._value == FLOATING) {
        return FLOATING;
    }
    return (_value==TRUE && v._value==TRUE)?TRUE:FALSE;
}

LogicValue::Value LogicValue::operator||(const LogicValue &v) const {
    if (_value == FLOATING || v._value == FLOATING) {
        return FLOATING;
    }
    return (_value==TRUE || v._value==TRUE)?TRUE:FALSE;
}
