#include <random>
#include <cstdint>

uint64_t generateRandomId64() {
    static std::random_device rd;
    static std::mt19937_64 gen(rd());
    static std::uniform_int_distribution<uint64_t> dist;

    return dist(gen);
}
