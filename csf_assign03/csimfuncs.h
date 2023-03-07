#ifdef CSIMFUNCS_H
#define CSIMFUNCS_H

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

#endif // CSIMFUNC_H