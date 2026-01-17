#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <string>
#include <cctype>
#include <windows.h>

std::string getStemName(const char* path) {
    std::string name = path;
    size_t dotPos = name.find_last_of('.');
    if (dotPos != std::string::npos) {
        name = name.substr(0, dotPos);
    }
    return name;
}

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(65001);

    if (argc != 2) {
        std::cout << "Usage: converter.exe <font.ttf>\n";
        std::cout << "Example: converter.exe arial.ttf\n";
        return 1;
    }

    std::ifstream file(argv[1], std::ios::binary | std::ios::ate);
    if (!file) {
        std::cout << "Error: Cannot open " << argv[1] << "\n";
        return 1;
    }

    auto size = file.tellg();
    file.seekg(0);
    std::vector<uint8_t> data(size);
    file.read(reinterpret_cast<char*>(data.data()), size);

    std::string outName = getStemName(argv[1]) + ".h";
    std::ofstream out(outName);
    if (!out) {
        std::cout << "Error: Cannot create " << outName << "\n";
        return 1;
    }

    std::time_t now = std::time(nullptr);
    struct tm timeinfo;
    localtime_s(&timeinfo, &now);
    char timeStr[64];
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &timeinfo);

    out << "// Generated at " << timeStr << "\n";
    out << "#pragma once\n";
    out << "static const unsigned char font_data[] = {\n";

    for (size_t i = 0; i < size; ++i) {
        out << "0x" << std::hex << std::uppercase << std::setw(2)
            << std::setfill('0') << static_cast<int>(data[i]);
        out << ((i + 1) % 16 == 0 ? ",\n" : ", ");
    }
    out << "};\n";
    out << "static const size_t font_size = " << size << ";\n";

    std::cout << "Generated: " << outName << "\n";
    std::cout << "Size: " << (size / 1024) << " KB (" << size << " bytes)\n";

    return 0;
}
