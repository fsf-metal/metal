#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <cstdlib>

using namespace std;

int main( int argc, char *argv[]) {
    string directory;
    string nameSpace;
    if( argc != 3) {
        cerr << "Usage: " << argv[0] << " {directory} {namespace}" << endl;
        exit(1);
    } else {
        directory = argv[1];
        nameSpace = argv[2];
    }
    cout << "Using : directory=" << directory << ", namespace=" << nameSpace << endl;

    string adapterFilename = directory + "__namespace__Adapter.cpp";
    std::ifstream t(adapterFilename.c_str());
    std::string adapterSource((std::istreambuf_iterator<char>(t)),
                     std::istreambuf_iterator<char>());

    // replace __namespace__ with second parameter
    size_t pos = 0;
    string pattern = "__namespace__";
    size_t len = pattern.length();
    while( ( pos = adapterSource.find( pattern, pos)) != string::npos) {
        adapterSource.replace( pos, len, nameSpace);
    }

    cout << adapterSource << endl;
}
