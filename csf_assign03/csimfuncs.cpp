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
#include <cstdint>



Cache* createEmptyCache(uint32_t numOfSets, uint32_t numOfBlocks) {
    std::vector<Set> sets;
    Cache* newCache = new Cache{sets, 0};
    // Initalize the sets in cache
    for (uint32_t i = 0; i < numOfSets; i++) {
        Set newSet;
        newSet.numOfSlots = 0;
        // Initalize the slots in sets
        for (uint32_t j = 0; j < numOfBlocks; j++) {
            Slot newSlot = {j, false, false, 0, 0};
            newSet.slots.push_back(newSlot);
        }
        newCache->sets.push_back(newSet);
    }
    return newCache;
}

uint32_t load_to_cache(Cache* mainCache, uint32_t index, uint32_t numOfBytes, uint32_t newTag, uint32_t numOfBlocks, bool lru) {
    Set* currentSet = &(mainCache->sets.at(index));
    // Punish for accessing memory
    mainCache->cycle += ((numOfBytes/4) * 100);
    if (currentSet->numOfSlots < numOfBlocks) {
        // Change the next empty slot to the newTag and update valid and ts
        currentSet->slots.at(currentSet->numOfSlots).tag = newTag;
        currentSet->slots.at(currentSet->numOfSlots).valid = true;
        currentSet->slots.at(currentSet->numOfSlots).load_ts = mainCache->cycle;
        currentSet->slots.at(currentSet->numOfSlots).access_ts = mainCache->cycle;
        
        // Add to map
        currentSet->indexMap.insert({newTag, &(currentSet->slots.at(currentSet->numOfSlots))});
        currentSet->numOfSlots++;
        return currentSet->numOfSlots;
    } else {
        // Search for LRU/FIFO
        uint32_t replacement = searchEvict(currentSet, lru);
        // Change slot to new tag
        currentSet->slots.at(replacement).tag = newTag;
        // Punish for dirty bit
        if (currentSet->slots.at(replacement).dirty) {
            mainCache->cycle += ((numOfBytes/4) * 100);
        }

        // Delete the tag from map
        currentSet->indexMap.erase(replacement);
        // Add to map
        currentSet->indexMap.insert({newTag, &(currentSet->slots.at(replacement))});
        // Update cycles
        currentSet->slots.at(replacement).load_ts = mainCache->cycle;
        currentSet->slots.at(replacement).access_ts = mainCache->cycle;
        return replacement;

    }

}

// Search for the tag that was hit
// If the tag was hit, return the slot with that tag, also update the LRU/FIFO
// If the tag was missed, return either a invalid slot
// If there are no invalid slot, return the LRU/FIFO slot
uint32_t searchEvict(Set* currentSet, bool lru) {
    uint32_t longest_load_ts = UINT32_MAX;
    uint32_t longest_access_ts = UINT32_MAX;

    uint32_t llt; // Update LRU
    uint32_t lat; // Update FIFO

    for (uint32_t i = 0; i < currentSet->numOfSlots; i++) {
        if (currentSet->slots.at(i).load_ts < longest_load_ts) {
            llt = i;
            longest_load_ts = currentSet->slots.at(i).load_ts;
        }
        if (currentSet->slots.at(i).access_ts < longest_access_ts) {
            lat = i;
            longest_access_ts = currentSet->slots.at(i).access_ts;
        }
    }
    if (!lru) {
        return llt;
    } else {
        return lat;
    }




    
}


