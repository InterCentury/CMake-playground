#include <iostream>
#include <string>

using namespace std;
 
// #include <dxgi.h> it requires windows sdk 
#if defined(_WIN32)
    #include <Windows.h>
    #include <dxgi.h>
    #pragma comment(lib, "dxgi.lib")
#elif defined(__linux__) || defined(__APPLE__)
    #include <array>
    #include <memory>
#endif 

string getGPUName() {
#if defined(_WIN32)
    IDXGIFactory* pFactory = nullptr;
    if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory))) {
        return "Failed to create DXGIFactory";
    }

    IDXGIAdapter* pAdapter = nullptr;
    string gpuName = "Unknown GPU";

    if (pFactory->EnumAdapters(0, &pAdapter) != DXGI_ERROR_NOT_FOUND) {
        DXGI_ADAPTER_DESC desc;
        pAdapter->GetDesc(&desc);
        wchar_t wgpu[128];
        wcstombs(gpuName.data(), desc.Description, 128);
        gpuName = string(desc.Description);
        pAdapter->Release();
    }

    pFactory->Release();
    return gpuName;

#elif defined(__linux__) || defined(__APPLE__)
    string result;
    array<char, 128> buffer;
    // Using system command to get GPU info
    unique_ptr<FILE, decltype(&pclose)> pipe(popen("lspci | grep VGA", "r"), pclose);
    if (!pipe) return "Failed to get GPU info";

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result.empty() ? "Unknown GPU" : result;

#else
    return "Unsupported OS";
#endif
}

int main() {
    cout << "GPU: " << getGPUName() << endl;
    return 0;
}
