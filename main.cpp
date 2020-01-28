#include "Server.h"

using namespace std;
using namespace server_side;

int main(int argc, char const *argv[]) {
  try {
    stoi(argv[1]);
  } catch (...) {
    cerr << "Missing or invalid port number (needs to be an integer)" << endl;
    exit(-1);
  }

  boot::Main m;
  string port = argv[1];
  m.main(port);

}
