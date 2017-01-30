cmake_minimum_required(VERSION 3.6)
project(logic)

add_definitions(-std=c++14 -Wall -pedantic)
include_directories(include)
include_directories(3rdparty/json11)

set(HEADER_FILES include/element.h
        include/logic-value.h
        include/pin.h
        include/isimulator.h
        include/exception.h
        include/elements/logic.h
        include/elements/user-logic.h
        include/elements/composition.h
        include/elements/generators/clock.h
        include/elements/generators/constant.h
        include/elements/logic/and.h
        include/elements/logic/nand.h
        include/elements/logic/nor.h
        include/elements/logic/not.h
        include/elements/logic/or.h
        include/simulator/simulator.h
        include/simulator/pin-change.h
        include/simulator/loader.h
        3rdparty/json11/json11.hpp
        )

set(SOURCE_FILES src/main.cpp
        src/element.cpp
        src/logic-value.cpp
        src/pin.cpp
        src/exception.cpp
        src/elements/logic.cpp
        src/elements/user-logic.cpp
        src/elements/composition.cpp
        src/simulator/simulator.cpp
        src/simulator/pin-change.cpp
        src/simulator/loader.cpp
        3rdparty/json11/json11.cpp)

add_executable(logic ${SOURCE_FILES} ${HEADER_FILES})
