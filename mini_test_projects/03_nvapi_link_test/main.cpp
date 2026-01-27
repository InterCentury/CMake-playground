#include <windows.h>
#include <iostream>
#include <Nvidia\nvapi.h>

int main()
{
    // Initialize NVAPI
    NvAPI_Status status = NvAPI_Initialize();
    if (status != NVAPI_OK)
    {
        std::cout << "NVAPI initialization failed!\n";
        return -1;
    }

    NvPhysicalGpuHandle gpuHandles[NVAPI_MAX_PHYSICAL_GPUS] = {};
    NvU32 gpuCount = 0;

    status = NvAPI_EnumPhysicalGPUs(gpuHandles, &gpuCount);
    if (status != NVAPI_OK || gpuCount == 0)
    {
        std::cout << "No NVIDIA GPU found.\n";
        return -1;
    }

    char gpuName[NVAPI_SHORT_STRING_MAX] = {};

    status = NvAPI_GPU_GetFullName(gpuHandles[0], gpuName);
    if (status != NVAPI_OK)
    {
        std::cout << "Failed to get GPU name.\n";
        return -1;
    }

    std::cout << "GPU Name: " << gpuName << std::endl;

    NvAPI_Unload();
    return 0;
}
