#include <string>
#include <iostream>

#include "cppnbstripoutlib.hpp"


int main(int argc, char* argv[]) {
  if (argc > 1) {
    std::string arg{argv[1]};

    if (arg == "-h") {
      std::cerr << "usage: cppnbstripout [INPUT] [OUTPUT]" << std::endl;
      return 0;
    }
  }

  std::string infile = "-";
  std::string outfile = "-";
  if (argc > 1) {
    infile = argv[1];
  }
  if (argc > 2) {
    outfile = argv[2];
  }


  cppnbstripout(infile, outfile);
}
