#include "csimfuncs.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <limits.h>
#include <math.h>
#include <unordered_map>
#include <cstdint>

void createEmptyCache(Cache *newCache, uint32_t numOfSets, uint32_t numOfBlocks)
{
    // std::vector<Set> sets;
    // Cache newCache;
    // Initalize the sets in cache
    for (uint32_t i = 0; i < numOfSets; i++)
    {
        Set newSet;
        newSet.numOfSlots = 0;
        // Initalize the slots in sets
        for (uint32_t j = 0; j < numOfBlocks; j++)
        {
            Slot newSlot = {0, false, false, 0, 0};
            newSet.slots.push_back(newSlot);
        }
        newCache->sets.push_back(newSet);
    }
    newCache->cycle = 0;
    newCache->counter = 0;
    // return &newCache;
}

uint32_t load_to_cache(Cache *mainCache, uint32_t index, uint32_t numOfBytes, uint32_t newTag, uint32_t numOfBlocks, bool lru)
{
    Set *currentSet = &(mainCache->sets.at(index));
    // Punish for accessing memory
    mainCache->cycle += ((numOfBytes / 4) * 100);

    if (currentSet->numOfSlots < numOfBlocks)
    {
        // Change the next empty slot to the newTag and update valid and ts
        currentSet->slots.at(currentSet->numOfSlots).tag = newTag;
        currentSet->slots.at(currentSet->numOfSlots).valid = true;
        currentSet->slots.at(currentSet->numOfSlots).load_ts = mainCache->counter;
        currentSet->slots.at(currentSet->numOfSlots).access_ts = mainCache->counter;
        currentSet->slots.at(currentSet->numOfSlots).dirty = false;

        // Add to map
        currentSet->indexMap.insert({newTag, &(currentSet->slots.at(currentSet->numOfSlots))});
        (currentSet->numOfSlots)++;
        return currentSet->numOfSlots - 1;
    }
    else
    {
        // Search for LRU/FIFO
        // gets the index of the block we want to replace
        uint32_t replacement = searchEvict(currentSet, lru);
        // get the tag of said block we want to replace
        uint32_t tagToEvict = currentSet->slots.at(replacement).tag;
        // deletes the old tag we want to replace
        currentSet->indexMap.erase(tagToEvict);
        // Change slot to new tag
        currentSet->slots.at(replacement).tag = newTag;
        // Punish for dirty bit
        if (currentSet->slots.at(replacement).dirty)
        {
            mainCache->cycle += ((numOfBytes / 4) * 100);
        }

        // Add to map
        currentSet->indexMap.insert({newTag, &(currentSet->slots.at(replacement))});
        // Update cycles
        currentSet->slots.at(replacement).load_ts = mainCache->counter;
        currentSet->slots.at(replacement).access_ts = mainCache->counter;

        // Make not dirty again
        currentSet->slots.at(replacement).dirty = false;
        return replacement;
    }
}

// Search for the tag that was hit
// If the tag was hit, return the slot with that tag, also update the LRU/FIFO
// If the tag was missed, return either a invalid slot
// If there are no invalid slot, return the LRU/FIFO slot
uint32_t searchEvict(Set *currentSet, bool lru)
{
    uint32_t longest_load_ts = currentSet->slots.at(0).load_ts;
    uint32_t longest_access_ts = currentSet->slots.at(0).access_ts;

    uint32_t llt = 0; // Update FIFO
    uint32_t lat = 0; // Update LRU

    for (uint32_t i = 1; i < currentSet->numOfSlots; i++)
    {
        if (currentSet->slots.at(i).load_ts < longest_load_ts)
        { // FIFO
            llt = i;
            longest_load_ts = currentSet->slots.at(i).load_ts;
        }
        if (currentSet->slots.at(i).access_ts < longest_access_ts)
        { // LRU
            lat = i;
            longest_access_ts = currentSet->slots.at(i).access_ts;
        }
    }
    if (lru)
    {
        return lat;
    }
    else
    {
        return llt;
    }
}

uint32_t getIndex(uint32_t address, uint32_t numOfSets, uint32_t numBytes)
{
    if (numOfSets == 1)
    { // Fully associative cache
        return 0;
    }
    uint32_t indexSize = log2(numOfSets);
    uint32_t offsetSize = log2(numBytes);

    uint32_t comparison = 0;

    for (uint32_t i = 0; i < indexSize; i++)
    {
        comparison = (comparison << 1) + 1;
    }

    for (uint32_t i = 0; i < offsetSize; i++)
    {
        address = address >> 1;
    }

    return address & comparison;
}
