#include <iostream>
#include <string>
#include <sstream>


 //  Platform Detection
 //  I can use this method for bianryfetch too...not bad 

#if defined(_WIN32)
    #define BF_WINDOWS
#elif defined(__linux__)
    #define BF_LINUX
#elif defined(__APPLE__)
    #define BF_MAC
#else
    #define BF_UNKNOWN
#endif 


// data models 

struct OSData {
    std::string name;
    std::string arch;
};

struct CPUData {
    std::string name;
    int cores;
};

// classes 
  
  

class OSInfo {
public:
    static OSData collect() {
        OSData data;

    #ifdef BF_WINDOWS
        data.name = "Windows";
        data.arch = "x64";
    #elif defined(BF_LINUX)
        data.name = "Linux";
        data.arch = "x64";
    #elif defined(BF_MAC)
        data.name = "macOS";
        data.arch = "ARM64 / x64";
    #else
        data.name = "Unknown OS";
        data.arch = "Unknown";
    #endif

        return data;
    }
};

class CPUInfo {
public:
    static CPUData collect() {
        CPUData data;

    #ifdef BF_WINDOWS
        data.name = "Generic Windows CPU";
        data.cores = 8;
    #elif defined(BF_LINUX)
        data.name = "Generic Linux CPU";
        data.cores = 8;
    #elif defined(BF_MAC)
        data.name = "Apple Silicon / Intel";
        data.cores = 8;
    #else
        data.name = "Unknown CPU";
        data.cores = 0;
    #endif

        return data;
    }
};


  //  Output Layer


class Printer {
public:
    static std::string renderOS(const OSData& os) {
        std::ostringstream ss;
        ss << "OS  : " << os.name << " (" << os.arch << ")";
        return ss.str();
    }

    static std::string renderCPU(const CPUData& cpu) {
        std::ostringstream ss;
        ss << "CPU : " << cpu.name << " (" << cpu.cores << " cores)";
        return ss.str();
    }
};

/* ============================
   main() – Orchestrator
   ============================ */

int main() {
    // Collect system data
    OSData os = OSInfo::collect();
    CPUData cpu = CPUInfo::collect();

    // Render output
    std::cout << Printer::renderOS(os) << "\n";
    std::cout << Printer::renderCPU(cpu) << "\n";

    return 0;
}
