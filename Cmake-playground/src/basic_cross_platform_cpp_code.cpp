#include <iostream>
#include <string>
using namespace std;
int main() {
    string os;

#if defined(_WIN32)
    os = "Windows";
#elif defined(__linux__)
    os = "Linux";
#elif defined(__APPLE__)
    os = "macOS";
#else
    os = "Unknown OS";
#endif

    cout << "Hello from C++ 👋" << endl;
    cout << "Running on: " << os << endl;

    return 0;
}
