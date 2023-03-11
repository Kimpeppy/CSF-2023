#ifndef CSIMFUNCS_H
#define CSIMFUNCS_H
#include <vector>
#include <map>
#include <unordered_map>

    struct Slot {
        long tag;
        bool valid;
        bool dirty;
        long load_ts, access_ts;
    };

    struct Set {
        std::vector<Slot> slots;
    };

    struct Cache {
        std::vector<Set> sets;
        long cycle; // Timer
    };

    // Create an empty cache and initalize it with empty values
    // It will process the parameter to make enough room for the cache 
    Cache createEmptyCache(long numOfBytes, long numOfSets, long numOfBlocks);
    
    // This function loads from memory to the cache
    // This function will only accept misses
    // Update the cache cycle
    void load_to_cache(Cache mainCache, Slot replacement, long numOfBytes, long newTag);

    // Find out which slot needs to be replace or find the slot that was hit
    // Returns either an invalid slot or LRU or FIFO slot
    Slot block_to_replace(std::vector<Slot> slot, Cache mainCache, bool lru);

#endif