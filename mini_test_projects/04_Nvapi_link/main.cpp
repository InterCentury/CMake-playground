#include <iostream>
#include "nvapi.h"

int main() {
    // 1. Initialize NVAPI
    if (NvAPI_Initialize() != NVAPI_OK) {
        std::cerr << "Failed to initialize NVAPI. Check your drivers!" << std::endl;
        return 1;
    }

    // 2. Get the first physical GPU handle
    NvPhysicalGpuHandle hPhysicalGpu[NVAPI_MAX_PHYSICAL_GPUS];
    NvU32 gpuCount = 0;
    
    if (NvAPI_EnumPhysicalGPUs(hPhysicalGpu, &gpuCount) != NVAPI_OK) {
        std::cerr << "Could not enumerate GPUs." << std::endl;
        return 1;
    }

    if (gpuCount == 0) {
        std::cout << "No NVIDIA GPUs detected." << std::endl;
        return 0;
    }

    // 3. Get and print the GPU name
    NvAPI_ShortString name;
    if (NvAPI_GPU_GetFullName(hPhysicalGpu[0], name) == NVAPI_OK) {
        std::cout << "Successfully linked NVAPI!" << std::endl;
        std::cout << "Primary GPU: " << name << std::endl;
    }

    // 4. Cleanup
    NvAPI_Unload();
    return 0;
}