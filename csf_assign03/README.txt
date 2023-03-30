Group members: Michael Kim, Afaf Saqib Qureshi

Contributions: 

For the second milestone, Afaf implemented the error handling in main.cpp and the code for storing values of the arguments from the
memory access trace file read from standard input. This was done to calculate the index, offset, and tag of the input address to 
compare with the cache address. Michael implemented all of the functions in csimfuncs.cpp and wrote the code for applying the 
conditional logic for the cache simulation in main.cpp (i.e., calculating hits, misses, cycles/general output for all possible cache 
configurations).

Afaf wrote the report for M3.


MILESTONE 3 REPORT:

For our cache simulator, the hypothetical memory size was chosen to be 512 KB or 512,000 bytes of memory. This data capacity was 
kept constant over all of the configurations.

The following configurations were varied using the gcc.trace file:

FOR DIRECT-MAPPED CACHE:
Since the total number of bytes in memory is 512,000, for a direct-mapped cache, the number of sets was calculated as follows 
(assuming there are a standard of 16 bytes stored in each block):
512,000/16 = 32000 ~ 32768 (rounded to the nearest positive power of 2 i.e., 2^15)

(1) ./csim 32768 1 16 write-allocate write-back fifo < gcc.trace
Results:
Total loads: 318197
Total stores: 197486
Load hits: 315816
Load misses: 2381
Store hits: 188593
Store misses: 8893
Total cycles: 5109190

(2) ./csim 32768 1 16 write-allocate write-back lru < gcc.trace
Results: 
Total loads: 318197
Total stores: 197486
Load hits: 315816
Load misses: 2381
Store hits: 188593
Store misses: 8893
Total cycles: 5109190

(3) ./csim 32768 1 16 no-write-allocate write-through fifo < gcc.trace
Results:
Total loads: 318197
Total stores: 197486
Load hits: 312176
Load misses: 6021
Store hits: 165174
Store misses: 32312
Total cycles: 22672683

(4) ./csim 32768 1 16 no-write-allocate write-through lru < gcc.trace
Results:
Total loads: 318197
Total stores: 197486
Load hits: 312176
Load misses: 6021
Store hits: 165174
Store misses: 32312
Total cycles: 22672683

Changing block size to see how it affects the results of each configuration i.e., (set a small block size of 8 bytes, and a 
larger block size of 32 bytes per block):

(5) ./csim 65536 1 8 write-allocate write-back fifo < gcc.trace
Results:
Total loads: 318197
Total stores: 197486
Load hits: 314534
Load misses: 3663
Store hits: 180088
Store misses: 17398
Total cycles: 4753885

(6) ./csim 65536 1 8 write-allocate write-back lru < gcc.trace
Results:
Total loads: 318197
Total stores: 197486
Load hits: 314534
Load misses: 3663
Store hits: 180088
Store misses: 17398
Total cycles: 4753885

If number of bytes 

(7) ./csim 16384 1 32 no-write-allocate write-through fifo < gcc.trace
Results:
Total loads: 318197
Total stores: 197486
Load hits: 314377
Load misses: 3820
Store hits: 169690
Store misses: 27796
Total cycles: 23320283

(8) ./csim 16384 1 32 no-write-allocate write-through lru < gcc.trace
Results:
Total loads: 318197
Total stores: 197486
Load hits: 314377
Load misses: 3820
Store hits: 169690
Store misses: 27796
Total cycles: 23320283

EXPLANATION: From all the results above, it can be seen that no significant differences were observed across any of the cache 
configurations because the number of cycles, hit, misses, etc, for both configurations are the same. This may be because of the 
ordering of the data in the trace file and the fact that both are valid eviction strategies. In this case, it may be that the data 
block being accessed is the one that's been least recently used/accessed (which accounts for the number of cycles it takes lru to 
access that data), and it may also have been one of the earliest added block (which accounts for the number of cycles it takes fifo 
to access that data). This could explain why the number of cycles for both configurations are stabilized/equal.


FOR SET-ASSOCIATIVE CACHE:
Since the total number of bytes in memory is 512,000, for a hypothetical 4-way set-associative cache, the number of sets was calculated
as follows (assuming there are a standard of 16 bytes stored in each of the 4 blocks):
512,000/(16*4) = 8000 ~ 8192 (rounded to the nearest positive power of 2 i.e., 2^13)

(1) ./csim 8192 4 16 write-allocate write-back fifo < gcc.trace
Results:
Total loads: 318197
Total stores: 197486
Load hits: 315851
Load misses: 2346
Store hits: 188613
Store misses: 8873
Total cycles: 5000810

(2) ./csim 8192 4 16 write-allocate write-back lru < gcc.trace
Results:
Total loads: 318197
Total stores: 197486
Load hits: 315852
Load misses: 2345
Store hits: 188613
Store misses: 8873
Total cycles: 5000010

(3) ./csim 8192 4 16 no-write-allocate write-through fifo < gcc.trace
Results:
Total loads: 318197
Total stores: 197486
Load hits: 312205
Load misses: 5992
Store hits: 165216
Store misses: 32270
Total cycles: 22661083

(4) ./csim 8192 4 16 no-write-allocate write-through lru < gcc.trace
Results:
Total loads: 318197
Total stores: 197486
Load hits: 312205
Load misses: 5992
Store hits: 165216
Store misses: 32270
Total cycles: 22661083

Changing block size to see how it affects the results of each configuration i.e., (set a small block size of 8 bytes, and a 
larger block size of 32 bytes per block):

(5) ./csim 16384 4 8 write-allocate write-back fifo < gcc.trace
Results:
Total loads: 318197
Total stores: 197486
Load hits: 314568
Load misses: 3629
Store hits: 180107
Store misses: 17379
Total cycles: 4702304

(6) ./csim 16384 4 8 write-allocate write-back lru < gcc.trace
Results:
Total loads: 318197
Total stores: 197486
Load hits: 314569
Load misses: 3628
Store hits: 180107
Store misses: 17379
Total cycles: 4701904

(7) ./csim 4096 4 32 no-write-allocate write-through fifo < gcc.trace
Results:
Total loads: 318197
Total stores: 197486
Load hits: 314405
Load misses: 3792
Store hits: 169733
Store misses: 27753
Total cycles: 23297883

(8) ./csim 4096 4 32 no-write-allocate write-through lru < gcc.trace
Results:
Total loads: 318197
Total stores: 197486
Load hits: 314406
Load misses: 3791
Store hits: 169733
Store misses: 27753
Total cycles: 23297083

EXPLANATION: Overall, the lru configurations had less access time compared to the fifo ones. This could be owed to the assumption 
that the data being accessed for eviction is stored in a memory location that has been accessed less frequently. Hence, lru's 
access time is shorter to evict the data that was the least-frequently accessed and keep the ones accessed many times after being added 
to cache memory. As for fifo, an item that was reused just recently might still be evicted from the cache even if it was inserted 
very early on. The fifo approach also reduced the hit rates of the cache relative to the ones for lru.


FOR FULLY-ASSOCIATIVE CACHE:
Since the total number of bytes in memory is 512,000, for a fully-associative cache, the number of blocks was calculated as follows 
(since there is only one set and there are a standard of 16 bytes stored in each of the blocks of the set):
512,000/16 = 32000 ~ 32768 (rounded to the nearest positive power of 2 i.e., 2^15)

(1) ./csim 1 32768 16 write-allocate write-back fifo < gcc.trace
Results:
Total loads: 318197
Total stores: 197486
Load hits: 315855
Load misses: 2342
Store hits: 188617
Store misses: 8869
Total cycles: 4991214

(2) ./csim 1 32768 16 write-allocate write-back lru < gcc.trace
Results:
Total loads: 318197
Total stores: 197486
Load hits: 315855
Load misses: 2342
Store hits: 188617
Store misses: 8869
Total cycles: 4991214

(3) ./csim 1 32768 16 no-write-allocate write-through fifo < gcc.trace
Results:
Total loads: 318197
Total stores: 197486
Load hits: 312207
Load misses: 5990
Store hits: 165216
Store misses: 32270
Total cycles: 22660283

(4) ./csim 1 32768 16 no-write-allocate write-through lru < gcc.trace
Results:
Total loads: 318197
Total stores: 197486
Load hits: 312207
Load misses: 5990
Store hits: 165216
Store misses: 32270
Total cycles: 22660283

Changing block size to see how it affects the results of each configuration i.e., (set a small block size of 8 bytes, and a 
larger block size of 32 bytes per block):

(5) ./csim 1 65536 8 write-allocate write-back fifo < gcc.trace
Results:
Total loads: 318197
Total stores: 197486
Load hits: 314571
Load misses: 3626
Store hits: 180111
Store misses: 17375
Total cycles: 4698508

(6) ./csim 1 65536 8 write-allocate write-back lru < gcc.trace
Results:
Total loads: 318197
Total stores: 197486
Load hits: 314571
Load misses: 3626
Store hits: 180111
Store misses: 17375
Total cycles: 4698508

(7) ./csim 1 16384 32 no-write-allocate write-through fifo < gcc.trace
Results:
Total loads: 318197
Total stores: 197486
Load hits: 314408
Load misses: 3789
Store hits: 169733
Store misses: 27753
Total cycles: 23295483

(8) ./csim 1 16384 32 no-write-allocate write-through lru < gcc.trace
Results:
otal loads: 318197
Total stores: 197486
Load hits: 314408
Load misses: 3789
Store hits: 169733
Store misses: 27753
Total cycles: 23295483

EXPLANATION: From the results above for a fully-associative cache, it can be seen that no significant differences were observed across 
any of the cache configurations because the number of cycles, hit, misses, etc, for both configurations are the same. In this case, 
it may be that the data being accessed is the one that's been least recently used/accessed (which accounts for the number of cycles 
it takes lru to access that data) and is one of the earliest added blocks (which accounts for the number of cycles it takes fifo to 
access that data). ALso, there is only 1 set in this cache to begin with which consists of all the blocks, any of which could contain 
the data to be accessed. One advantage of the fully-associative cache is therefore that it permits data to be stored in any cache block 
instead of forcing each memory address into one particular block. This way, when the data is accessed from memory, it can be placed in 
any of the unused blocks of the cache. This could explain why the number of cycles are stabilized/equal for both configurations 
regardless of the eviction strategies employed.

OVERALL CONCLUSION: Based on the noticeable differences from the varying configurations for the 4-way set-associative cache, we can
consider the lru strategy to be the "best" cache configuration, in this case. The reason is that it had significantly less access time/
took less number of cycles to retrieve data from memory compared to fifo.
