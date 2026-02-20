#include <iostream>
#include <vector>
#include "nvapi.h"

int main() {
    // 1. Initialize the NVAPI library
    NvAPI_Status status = NvAPI_Initialize();
    if (status != NVAPI_OK) {
        std::cerr << "NVAPI Initialization failed! Error code: " << status << std::endl;
        return 1;
    }

    // 2. Enumerate Physical GPUs
    NvPhysicalGpuHandle gpuHandles[NVAPI_MAX_PHYSICAL_GPUS];
    NvU32 gpuCount = 0;
    status = NvAPI_EnumPhysicalGPUs(gpuHandles, &gpuCount);

    if (status != NVAPI_OK || gpuCount == 0) {
        std::cerr << "No NVIDIA GPUs found or enumeration failed." << std::endl;
        NvAPI_Unload();
        return 1;
    }

    std::cout << "Detected " << gpuCount << " NVIDIA GPU(s):" << std::endl;

    // 3. Retrieve and print the GPU name
    for (NvU32 i = 0; i < gpuCount; ++i) {
        NvAPI_ShortString name;
        if (NvAPI_GPU_GetFullName(gpuHandles[i], name) == NVAPI_OK) {
            std::cout << " -> GPU " << i << ": " << name << std::endl;
        }
    }

    // 4. Cleanup
    NvAPI_Unload();
    std::cout << "\nTest complete. Press Enter to exit...";
    std::cin.get();
    
    return 0;
}