#include "csimfuncs.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <cstring>
#include <cmath>


using std::strcmp;
using std::cerr;
using std::ceil;
using std::floor;
using std::log2;
using std::cin;
using std::cout;
using std::endl;
using std::stoi;
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
    if (!(isdigit(*(argv[1]))) && !(isdigit(*(argv[2]))) && !(isdigit(*(argv[3])))) 
    {
        cerr << "Invalid arguments";
        return 1;
    }

    // Check to see if string arguments are of a valid type
    if (!(strcmp(argv[4], "no-write-allocate") == 0) && !(strcmp(argv[4], "write-allocate") == 0))
    {
        
        cerr << "Invalid arguments";
        return 1;
    }

    if (!(strcmp(argv[5], "write-through") == 0) && !(strcmp(argv[5], "write-back") == 0))
    {
        cerr << "Invalid arguments";
        return 1;
    }

    if (!(strcmp(argv[6], "lru") == 0) && !(strcmp(argv[6], "fifo") == 0))
    {
        cerr << "Invalid arguments";
        return 1;
    }

    // Convert arguments to integer values
    uint32_t numBlockBytes = stoi(argv[3]);
    uint32_t numSets = stoi(argv[1]);
    uint32_t numBlocks = stoi(argv[2]);

    // Check that block size is valid if it is not less than 4
    if (numBlockBytes < 4) 
    {
        cerr << "Invalid arguments";
        return 1;
    }
    
    // Check that block size is valid if it is a power of 2
    if ((numBlockBytes & (numBlockBytes - 1)) != 0) 
    {
        cerr << "Invalid arguments";
        return 1;
    }

    // Check that number of sets in the cache is valid if it is a power of 2
    if ((numSets & (numSets - 1)) != 0) 
    {
        cerr << "Invalid arguments";
        return 1;
    }

    // Check if write-back and no-write-allocate were both specified
    if ((strcmp(argv[4], "no-write-allocate") == 0) && (strcmp(argv[5], "write-back") == 0))
    {
        cerr << "Invalid arguments";
        return 1;
    }
  
    // Create empty cache with input arguments and
    // calculate the index, offset, and tag of the given address
    Cache cacheSim;
    createEmptyCache(&cacheSim, numSets, numBlocks);
    uint32_t indexSize = log2(numSets);
    uint32_t offsetSize = log2(numBlockBytes);
    uint32_t tagSize = 32 - (indexSize + offsetSize);

    

    // Store values read from memory access trace from standard input
    char first_arg;
    uint32_t address;
    // char garbage;
    uint32_t index;
    // uint32_t bitmask;
    uint32_t tag;
    bool lru;
    if (strcmp(argv[6], "lru")) {
        lru = true;
    } else if (strcmp(argv[6], "fifo")) {
        lru = false;
    }
    
    uint32_t total_loads = 0;
    uint32_t total_stores = 0;
    uint32_t load_hits = 0;
    uint32_t load_misses = 0;
    uint32_t store_hits = 0;
    uint32_t store_misses = 0;
    uint32_t total_cycles = 0;
    
    // Way to find location of the related slot
    uint32_t location = 0;

    // Bool of if the tag was hit or miss
    bool hit;


    // Work in progress for conditional logic
    // Read in chained data from standard input
    // Use std::hex to convert the string address to hex
    while (cin >> first_arg >> std::hex >> address /* >> garbage */) 
    {

        // Make hit false
        hit = false;
        // Get the current set
        // Get the memory address of the index and tag
        index = (address << tagSize) >> (tagSize + offsetSize);
        

        // Get the tag address
        tag = address >> (indexSize + offsetSize);

        //Search if the cache hit or miss

        std::map<uint32_t, Slot*>::iterator itr = cacheSim.sets.at(index).indexMap.find(tag);
        if (itr != cacheSim.sets.at(index).indexMap.end()) {
            hit = true;
        }

        // If the cache load
        if (first_arg == 'l') {
            total_loads++;
            //if tag miss
            if (!hit) {
                load_misses++;
                location = load_to_cache(&cacheSim, index, numBlockBytes, tag, numBlocks, lru);
                cacheSim.cycle++;
                cacheSim.sets.at(index).slots.at(location).access_ts = cacheSim.cycle;
            }
            // if tag hit
            else {
                location = itr->second->id;
                load_hits++;
                cacheSim.cycle++;
                cacheSim.sets.at(index).slots.at(location).access_ts = cacheSim.cycle;
                
                // cacheSim->sets.at(index).slots.at(tag).access_ts = cacheSim->cycle;
            }
        }
        else if (first_arg == 's') {
            total_stores++;
            // If the policies is WA/WB
            
            if (strcmp(argv[4], "write-allocate") == 0 && strcmp(argv[5], "write-back") == 0) {
                //if tag miss
                if (!hit) {
                    store_misses++;
                    location = load_to_cache(&cacheSim, index, numBlockBytes, tag, numBlocks, lru);
                    cacheSim.cycle++;
                    cacheSim.sets.at(index).slots.at(location).access_ts = cacheSim.cycle;
                    cacheSim.sets.at(index).slots.at(location).dirty = true;

                    
                }
                // if tag hit
                else {
                    location = itr->second->id;
                    store_hits++;
                    cacheSim.cycle++;
                    cacheSim.sets.at(index).slots.at(location).access_ts = cacheSim.cycle;
                    cacheSim.sets.at(index).slots.at(location).dirty = true;
                    
                }
                
            }
            
            else if (strcmp(argv[4], "write-allocate") == 0 && strcmp(argv[5], "write-through") == 0) {
                // if tag miss
                //if tag miss

                if (!hit) {
                    store_misses++;
                    location = load_to_cache(&cacheSim, index, numBlockBytes, tag, numBlocks, lru);
                    cacheSim.cycle += 100;
                    cacheSim.sets.at(index).slots.at(location).access_ts = cacheSim.cycle;

                }
                // if tag hit
                else {
                    location = itr->second->id;
                    store_hits++;
                    cacheSim.cycle += 100;
                    cacheSim.sets.at(index).slots.at(location).access_ts = cacheSim.cycle;
                }
            }
            else if (strcmp(argv[4], "no-write-allocate") == 0 && strcmp(argv[5], "write-through") == 0) {
                //if tag miss

                if (!hit) {
                    store_misses++;
                    cacheSim.cycle+= 100;
                }
                // if tag hit
                else {
                    location = itr->second->id;
                    store_hits++;
                    cacheSim.cycle+= 100;
                    cacheSim.sets.at(index).slots.at(location).access_ts = cacheSim.cycle;
                }
            }
        }
        

        std::cin.ignore(5, '\n');

    }

    total_cycles = cacheSim.cycle;

    cout << "Total loads: " << total_loads << endl;
    cout << "Total stores: " << total_stores << endl;
    cout << "Load hits: " << load_hits << endl;
    cout << "Load misses: " << load_misses << endl;
    cout << "Store hits: " << store_hits << endl;
    cout << "Store misses: " << store_misses << endl;
    cout << "Total cycles: " << total_cycles << endl;

 
    




    

}