// CONFIG FILE
#pragma once
#include <vector>

#ifdef MYON_DEBUG
const bool enableValidationLayers = true;
#else
const bool enableValidationLayers = false;
#endif

const std::vector<const char *> validationLayers = {
    "VK_LAYER_KHRONOS_validation"};
