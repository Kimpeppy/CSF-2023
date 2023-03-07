#include "csimfuncs.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

struct Slot {
    uint32_t tag;
    bool valid;
    uint32_t load_ts, access_ts;
};

struct Set {
    std::vector<Slot> slots;
};

struct Cache {
    std::vector<Set> sets;
};

// Note
// Use STDHEX to change the hex to a string
int main(int argc, char* argv[]) {
    if (argc != 4) {
        std :: cout<<"Invalid arguments" << std::endl;
        return 1;
    }
    std::istringstream converter { argv[2] };

    long address = 0;
    converter >> std::hex >> address;

    std :: cout << address << std::endl;

    
}