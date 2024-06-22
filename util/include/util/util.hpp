#pragma once

#include <string>
#include <filesystem>

namespace util {

std::string readFileToString(const std::filesystem::path& filepath);

}
