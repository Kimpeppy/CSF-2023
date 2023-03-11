#include "csimfuncs.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::stoi;
using std::ifstream;
using std::string;


int main(int argc, char *argv[])
{
    // Error handling
    // If number of arguments is not correct, exit with code 1
    if (argc < 6)
    {
        cerr << "Invalid arguments";
        return 1;
    }

    // Check to see if int arguments are of a valid type/consist an actual number
    if (!(isdigit(arg[1])) | !(isdigit(arg[2])) | !(isdigit(arg[3]))) 
    {
        cerr << "Invalid arguments";
        return 1;
    }

    // Check to see if string arguments are of a valid type
    if (!(arg[4].equals("no-write-allocate")) | !(arg[4].equals("write-allocate"))) 
    {
        cerr << "Invalid arguments";
        return 1;
    }

    if (!(arg[5].equals("write-through")) | !(arg[5].equals("write-back"))) 
    {
        cerr << "Invalid arguments";
        return 1;
    }

    if (!(arg[4].equals("lru")) | !(arg[4].equals("fifo")))
    {
        cerr << "Invalid arguments";
        return 1;
    }

    // Convert arguments to integer values
    int numBlockBytes = stoi(arg[3]);
    int numSets = stoi(arg[1]);
    int numBlocks = stoi(arg[2]);

    // Check that block size is valid if it is not less than 4
    if (numBlockBytes < 4) 
    {
        cerr << "Invalid arguments";
        return 1;
    }
    
    // Check that block size is valid if it is a power of 2
    if (ceil(log2(numBlockBytes)) != floor(log2(numBlockBytes))) 
    {
        cerr << "Invalid arguments";
        return 1;
    }

    // Check that number of sets in the cache is valid if it is a power of 2
    if (ceil(log2(numSets)) != floor(log2(numSets))) 
    {
        cerr << "Invalid arguments";
        return 1;
    }

    // Check if write-back and no-write-allocate were both specified
    if (arg[4].equals("no-write-allocate") && arg[5].equals("write-back"))
    {
        cerr << "Invalid arguments";
        return 1;
    }
  
    // Create empty cache with input arguments and
    // calculate the index, offset, and tag of the given address
    Cache cacheSim = createEmptyCache(numBlockBytes, numSets, numBlocks);
    uint32_t index = log2(numSets);
    uint32_t offset = log2(numBlockBytes);
    uint32_t tag = 32 - (index + offset);

    // Store values read from memory access trace from standard input
    char first_arg;
    uint32_t address;
    char garbage;
    
    // Read in chained data from standard input
    // Use std::hex to convert the string address to hex
    while (cin >> first_arg >> std::hex >> address >> garbage) 
    {
        if (first_arg == 's') {
            
        }   
    }

}