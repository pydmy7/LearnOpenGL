#include "util/util.hpp"

#include <fstream>
#include <sstream>

namespace util {

std::string readFileToString(const std::filesystem::path& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file!\n");
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

}
