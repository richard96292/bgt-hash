#include <getopt.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "hash.hpp"
using namespace std;

string outputHelp() {
  stringstream res;
  res << "pass -f and a filename to read from a file\n"
      << "pass -s to read from stdin\n"
      << "pass -m and a quoted string to mine hashes (test puzzle friendliness)"
      << "pass -b to run a suite of tests (files must be generated "
         "beforehand)\n"
      << "pass -n to and a filename and number of lines as an argument. Format "
         "is \"2 file.txt\" (dont forget quotes)\n";
  return res.str();
}

int main(int argc, char* argv[]) {
  int c, index;
  Hash h;

  if (argc == 1) {
    cout << outputHelp();
    return 42;
  }

  while ((c = getopt(argc, argv, "f:n:s:hbm:")) != -1) {
    switch (c) {
      case 'f':
        try {
          cout << h.callHashingFunctionFile(optarg) << endl;
          break;
        } catch (const string& err) {
          cerr << err;
          return EXIT_FAILURE;
        }
      case 'm':
        h.mine(optarg, "000000");
        break;
      case 'n':
        try {
          h.callHashingFunctionNStrings(optarg);
          break;
        } catch (const string& err) {
          cerr << err;
          return EXIT_FAILURE;
        }
      case 's':
        cout << h.callHashingFunctionString(optarg) << endl;
        break;
      case 'h':
        cout << outputHelp();
        break;
      case 'b':
        try {
          h.benchmark();
          break;
        } catch (const string& err) {
          cerr << err;
          return EXIT_FAILURE;
        }
      case '?':
        return 42;
      default:
        abort();
    }
  }

  for (index = optind; index < argc; index++)
    printf("Non-option argument %s\n", argv[index]);

  return 0;
}
