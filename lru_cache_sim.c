#include <stdio.h>
#include <stdbool.h>

#define CACHE_CAPACITY 4

// Structure to represent a single cache line / block
typedef struct {
    int page_id;
    int access_timestamp;
    bool valid;
} CacheBlock;

CacheBlock cache[CACHE_CAPACITY];
int global_timer = 0;

// Initialize cache blocks
void initialize_cache() {
    for (int i = 0; i < CACHE_CAPACITY; i++) {
        cache[i].page_id = -1;
        cache[i].access_timestamp = 0;
        cache[i].valid = false;
    }
}

// Function to simulate memory access via LRU policy
bool access_memory(int page_id, int *evicted_page) {
    global_timer++;
    *evicted_page = -1;

    // 1. Check for Cache HIT
    for (int i = 0; i < CACHE_CAPACITY; i++) {
        if (cache[i].valid && cache[i].page_id == page_id) {
            cache[i].access_timestamp = global_timer; // Update access time
            return true; // Cache Hit
        }
    }

    // 2. Cache MISS: Check for an empty (invalid) slot first
    for (int i = 0; i < CACHE_CAPACITY; i++) {
        if (!cache[i].valid) {
            cache[i].page_id = page_id;
            cache[i].access_timestamp = global_timer;
            cache[i].valid = true;
            return false; // Cache Miss (Compulsory)
        }
    }

    // 3. Cache MISS & FULL: Find the Least Recently Used (LRU) block to replace
    int lru_index = 0;
    int oldest_time = cache[0].access_timestamp;

    for (int i = 1; i < CACHE_CAPACITY; i++) {
        if (cache[i].access_timestamp < oldest_time) {
            oldest_time = cache[i].access_timestamp;
            lru_index = i;
        }
    }

    // Evict the LRU block and insert the new page
    *evicted_page = cache[lru_index].page_id;
    cache[lru_index].page_id = page_id;
    cache[lru_index].access_timestamp = global_timer;

    return false; // Cache Miss with Eviction
}

// Display current cache contents
void print_cache_state() {
    printf("  [Cache State]: ");
    for (int i = 0; i < CACHE_CAPACITY; i++) {
        if (cache[i].valid)
            printf("[%d] ", cache[i].page_id);
        else
            printf("[ ] ");
    }
    printf("\n");
}

int main() {
    // Simulated memory address stream
    int memory_references[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int total_requests = sizeof(memory_references) / sizeof(memory_references[0]);
    int hits = 0;
    int misses = 0;
    int evicted_page = -1;

    initialize_cache();

    printf("============================================================\n");
    printf("  LRU Cache Architecture Simulator (Capacity: %d blocks)\n", CACHE_CAPACITY);
    printf("============================================================\n\n");

    for (int i = 0; i < total_requests; i++) {
        int page = memory_references[i];
        printf("Request %2d -> Access Page: %d | ", i + 1, page);

        if (access_memory(page, &evicted_page)) {
            hits++;
            printf("Result: HIT!         ");
        } else {
            misses++;
            if (evicted_page != -1)
                printf("Result: MISS (Evict %d)", evicted_page);
            else
                printf("Result: MISS (Empty)   ");
        }
        print_cache_state();
    }

    // Statistical Summary
    float hit_ratio = ((float)hits / total_requests) * 100.0;
    float miss_ratio = ((float)misses / total_requests) * 100.0;

    printf("\n------------------------------------------------------------\n");
    printf("               SIMULATION PERFORMANCE SUMMARY               \n");
    printf("------------------------------------------------------------\n");
    printf("Total Memory Accesses : %d\n", total_requests);
    printf("Cache Hits            : %d\n", hits);
    printf("Cache Misses          : %d\n", misses);
    printf("Hit Ratio             : %.2f%%\n", hit_ratio);
    printf("Miss Ratio            : %.2f%%\n", miss_ratio);
    printf("============================================================\n");

    return 0;
}
