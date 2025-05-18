#include <random>
#include <cstdint>
#include <string>
#include <raylib.h>

uint64_t generateRandomId64() {
    static std::random_device rd;
    static std::mt19937_64 gen(rd());
    static std::uniform_int_distribution<uint64_t> dist;

    return dist(gen);
}

std::string getAssetPath(const char* file) {
    return std::string(GetApplicationDirectory()) + "\\assets\\" + file;
}

