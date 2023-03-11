#include "csimfuncs.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using std::cin;
using std::stoi
using std::cout;
using std::endl;
using std::ifstream;
using std::map;
using std::string;
using std::vector;


int main(int argc, char *argv[])
{
    // if number of arguments is not correct, exit with code 1
    if (argc < 6)
    {
        cout << "Invalid arguments";
        return 1;
    }

    char first_arg;
    uint32_t address;
    char garbage;
    // Convert arguments to integer values
    int numBlockBytes = stoi(arg[2]);
    int numSets = stoi(arg[0]);
    int numBlocks = stoi(arg[1]);
    
    // Create empty cache with input arguments
    createEmptyCache(numBlockBytes, numSets, numBlocks);
    uint32_t index;
    uint32_t offset;
    index = log2(numSets);
    offset = log2(numBlockBytes);
    
    // Read in chained data from standard input
    // Use std::hex to convert the string address to hex
    while (cin >> first_arg >> std::hex >> address >> garbage) 
    {
           
    }

}