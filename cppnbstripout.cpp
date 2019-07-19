#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using nlohmann::json;

void clean(json& j) {
  json& cells = j["cells"];

  for (auto& cell : cells) {
    if (cell["execution_count"] != nullptr) {
      cell["execution_count"] = 0;
    }
    cell["outputs"] = json::array();
  }
}

int main(int argc, char* argv[]) {
  if (argc > 1) {
    std::string arg{argv[1]};

    if (arg == "-h") {
      std::cerr << "usage: cppnbstripout [INPUT] [OUTPUT]" << std::endl;
      return 0;
    }
  }

  std::unique_ptr<std::istream> ifs{nullptr};
  std::unique_ptr<std::ostream> ofs{nullptr};

  std::istream* is{&std::cin};
  std::ostream* os{&std::cout};

  std::string infile = "-";
  std::string outfile = "-";
  if (argc > 1) {
    infile = argv[1];
  }
  if (argc > 2) {
    outfile = argv[2];
  }

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
