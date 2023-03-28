#ifndef CSIMFUNCS_H
#define CSIMFUNCS_H
#include <vector>
#include <map>
#include <unordered_map>
#include <cstdint>

    struct Slot {
        uint32_t tag;
        bool valid;
        bool dirty;
        uint32_t load_ts, access_ts;
    };

    struct Set {
        std::vector<Slot> slots;
        std::map<uint32_t, Slot *> indexMap;
        uint32_t numOfSlots;
    };

    struct Cache{
        std::vector<Set> sets;
        uint32_t cycle; // Timer
        uint32_t counter; //counter
    };

    // Create an empty cache and initalize it with empty values
    // It will process the parameter to make enough room for the cache 
    void createEmptyCache(Cache *newCache, uint32_t numOfSets, uint32_t numOfBlocks);
    
    // This function loads from memory to the cache
    // This function will only accept misses
    // Update the cache cycle
    uint32_t load_to_cache(Cache* mainCache, uint32_t index, uint32_t numOfBytes, uint32_t newTag, uint32_t numOfBlocks, bool lru);

    // Find out which slot needs to be replace or find the slot that was hit
    // Returns either an invalid slot or LRU or FIFO slot
    uint32_t searchEvict(Set* currentSet, bool lru);

    uint32_t getIndex(uint32_t address, uint32_t numOfSets, uint32_t numBytes);





#endif