#include "csimfuncs.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <limits.h>
#include <unordered_map>



Cache* createEmptyCache(long cycle, long numOfBytes, long numOfSets, long numOfBlocks) {
    Cache newCache;
    // Initalize the sets in cache
    for (long i = 0; i < numOfSets; i++) {
        Set newSet;
        // Initalize the slots in sets
        for (long j = 0; j < numOfBlocks; j++) {
            Slot newSlot = {j, false, false, 0, 0};
            newSet.slots.push_back(newSlot);
        }
        newCache.sets.push_back(newSet);
    }
    return &newCache;
}

void load_to_cache(Cache mainCache, Slot replacement, long numOfBytes, long newTag) {
    mainCache.cycle += (numOfBytes/4) * 100;
    // Find the slots of the sets
    // Punish for dirty bit
    if (replacement.dirty) {
        mainCache.cycle += (numOfBytes/4) * 100;
    }
    if (!(replacement.valid)) {
        replacement.valid = true;
    }
    replacement.tag = newTag;
    replacement.load_ts = mainCache.cycle;
    replacement.access_ts = mainCache.cycle;

}

Slot block_to_replace(std::vector<Slot> slot, Cache mainCache, bool lru, long tag) {
    // Do a linear search to find where the valid index is
    // Break if you find a valid index
    // Track lowest load_ts and highest access_ts
    long longest_load_ts = 0;
    long longest_access_ts = 0;

    Slot llt;
    Slot lat;

    
    for (Slot& it: slot) {
        if (!(it.valid)) {
            return it;
        }
        if (it.load_ts > longest_load_ts) {
            longest_load_ts = it.load_ts;
            llt = it;
        }
        if (it.access_ts > longest_access_ts) {
            longest_access_ts = it.access_ts;
            lat = it;
        }
    }
    if (lru) {
        return llt;
    } else {
        return lat;
    }

}