#include "cppnbstripoutlib.hpp"

#include <string>
#include <fstream>
#include <iostream>
#include <memory>

#include <nlohmann/json.hpp>

using nlohmann::json;

void clean(json& j) {
  j["metadata"]["language_info"]["version"] = nullptr;

  json& cells = j["cells"];

  for (auto& cell : cells) {
    if (cell["execution_count"] != nullptr) {
      cell["execution_count"] = 0;
    }
    cell["outputs"] = json::array();
  }
}

void cppnbstripout(const std::string& infile, const std::string& outfile) {

  std::unique_ptr<std::istream> ifs{nullptr};
  std::unique_ptr<std::ostream> ofs{nullptr};

  std::istream* is{&std::cin};
  std::ostream* os{&std::cout};


  if (infile != "-") {
    ifs = std::make_unique<std::ifstream>(infile);
    is = ifs.get();
  }

  // open - read - close, so it doesn't matter where we write to
  json input;
  (*is) >> input;

  clean(input);

  if (outfile == "") {
    // save to input file
    ofs = std::make_unique<std::ofstream>(
        infile);  // this truncates the input file
    os = ofs.get();

  } else if (outfile == "-") {
    // use stdout
    os = &std::cout;
  } else {
    ofs = std::make_unique<std::ofstream>(outfile);
    os = ofs.get();
  }

  (*os) << input.dump(1);
  (*os) << "\n";

}
