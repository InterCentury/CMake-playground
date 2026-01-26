#include <windows.h>
#include <dxgi.h>
#include <iostream>

#pragma comment(lib, "dxgi.lib")

int main() {
    HRESULT hr = CoInitialize(nullptr);
    if (FAILED(hr)) {
        std::cerr << "COM initialization failed\n";
        return 1;
    }

    IDXGIFactory* factory = nullptr;
    hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
    if (FAILED(hr)) {
        std::cerr << "Failed to create DXGI Factory\n";
        CoUninitialize();
        return 1;
    }

    IDXGIAdapter* adapter = nullptr;
    if (factory->EnumAdapters(0, &adapter) == DXGI_ERROR_NOT_FOUND) {
        std::cerr << "No GPU found\n";
        factory->Release();
        CoUninitialize();
        return 1;
    }

    DXGI_ADAPTER_DESC desc;
    adapter->GetDesc(&desc);

    std::wcout << L"GPU : " << desc.Description << std::endl;

    adapter->Release();
    factory->Release();
    CoUninitialize();

    return 0;
}
