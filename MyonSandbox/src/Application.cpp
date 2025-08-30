#include "MyonRuntime.hpp"

int main()
{
    MyonR::MyonRuntimeConfig runtimeConfig{
        .name = "MyonSandbox",
        .width = 800,
        .height = 600
    };

    MyonR::MyonRuntime runtime{&runtimeConfig};

    while (!runtime.shouldClose)
    {
        runtime.PollEvents();
    }
}
