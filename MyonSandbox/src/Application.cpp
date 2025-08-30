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

        auto colorTargetInfo = gfx->createColorTargetInfo();
        colorTargetInfo.clear_color = { 255.0f, 0.0f, 0.0f, 255.0f };
        colorTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR;
        colorTargetInfo.store_op = SDL_GPU_STOREOP_STORE;
        colorTargetInfo.mip_level = 0;
        colorTargetInfo.layer_or_depth_plane = 0;
        colorTargetInfo.cycle = false;

        auto renderPass = gfx->beginRenderPass(&colorTargetInfo, 1);
        gfx->endRenderPass(renderPass);

        gfx->submit();
    }
}
