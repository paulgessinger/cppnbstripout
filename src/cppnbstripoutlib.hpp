#pragma once

#include <string>

#include <nlohmann/json.hpp>

void clean(nlohmann::json& j);

void cppnbstripout(const std::string& infile, const std::string& outfile);
