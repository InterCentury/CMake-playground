#include <iostream>
#include "nvapi.h"

int main() {
    // 1. Initialize NVAPI
    if (NvAPI_Initialize() != NVAPI_OK) {
        std::cerr << "❌ NVAPI Init Failed!" << std::endl;
        return 1;
    }

    // 2. Get Handles
    NvPhysicalGpuHandle gpuHandles[NVAPI_MAX_PHYSICAL_GPUS];
    NvU32 gpuCount = 0;
    NvAPI_EnumPhysicalGPUs(gpuHandles, &gpuCount);

    if (gpuCount == 0) {
        std::cout << "🚫 No NVIDIA GPUs found." << std::endl;
    } else {
        std::cout << "✅ Found " << gpuCount << " GPU(s):" << std::endl;
        
        for (NvU32 i = 0; i < gpuCount; ++i) {
            NvAPI_ShortString name;
            if (NvAPI_GPU_GetFullName(gpuHandles[i], name) == NVAPI_OK) {
                std::cout << "   - [" << i << "] " << name << std::endl;
            }
        }
    }

    // 3. Cleanup
    NvAPI_Unload();
    return 0;
}