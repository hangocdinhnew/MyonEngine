#include "MyonRuntime.hpp"

int main()
{
    MyonR::MyonRuntimeConfig runtimeConfig{
        .name = "MyonSandbox",
        .width = 800,
        .height = 600
    };

    MyonR::MyonRuntime runtime{&runtimeConfig};
    auto gfx = runtime.getGraphics();
    gfx->setSwapchainParameters(SDL_GPU_SWAPCHAINCOMPOSITION_SDR, SDL_GPU_PRESENTMODE_VSYNC);

    while (!runtime.shouldClose)
    {
        runtime.PollEvents();
        gfx->acquireCmdBuffer();
        gfx->acquireTexture();

        gfx->clearColor(255.0f, 0.0f, 0.0f, 255.0f);

        gfx->submit();
    }
}
