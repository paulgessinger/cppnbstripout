#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <argparse.hpp>


using nlohmann::json;

void clean(json& j, bool strip_kernel_spec) {
  // j["metadata"]["language_info"]["version"] = nullptr;

  json& cells = j["cells"];

  for (auto& cell : cells) {
    if (cell.find("execution_count") != cell.end()) {
      if (!cell["execution_count"].is_null()) {
        if (cell["execution_count"].get<int>() != 0) {
          cell["execution_count"] = nullptr;
        }
      }
    }
    if (cell.find("outputs") != cell.end()) {
      cell["outputs"] = json::array();
    }
    if (cell.find("metadata") != cell.end()) {
      cell["metadata"] = json::object();
    }
  }

  if(strip_kernel_spec) {
    j["metadata"]["kernelspec"] = nullptr;
  }
}

int main(int argc, char* argv[]) {
  argparse::ArgumentParser program("cppnbstripout");

  program.add_argument("--kernel-spec").default_value(false).implicit_value(true);
  program.add_argument("args").remaining();

  try {
    program.parse_args(argc, argv);
  }
  catch (const std::runtime_error& err) {
    std::cout << err.what() << std::endl;
    std::cout << program;
    exit(0);
  }

  std::vector<std::string> args;
  try {
    args = program.get<std::vector<std::string>>("args");
  } 
  catch (const std::logic_error&) {
  }

  if(args.size() > 2) {
    throw std::runtime_error("Too many arguments");
  }


  bool strip_kernel_spec = program.get<bool>("--kernel-spec");

  std::string infile = "-";
  std::string outfile = "-";
    
  if(args.size() == 2) {
    infile = args[0];
    outfile = args[1];
  }

  if(args.size() == 1) {
    infile = args[0];
  }

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

  clean(input, strip_kernel_spec);

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
