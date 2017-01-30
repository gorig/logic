#include <cstdio>
#include <exception.h>
#include <simulator/simulator.h>
#include <simulator/loader.h>

using namespace std::chrono_literals;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s root_file.json\n", argv[0]);
        return 1;
    }

    try {
        simulator::Simulator simulator;
        simulator::Loader loader(simulator);
        loader.Load(argv[1]);
        simulator.Run(1us);
        simulator.Terminate();

        printf("%s\n", simulator.GetResult().dump().c_str());
    } catch (Exception e) {
        printf("%s\n", e.what());
    }

    return 0;
}