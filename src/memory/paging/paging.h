
#ifndef AGNETAOS_PAGING_H
#define AGNETAOS_PAGING_H

#include <stdint.h>
#include <stddef.h>

#define PAGING_CACHE_DISABLED        0b00010000
#define PAGING__WRITE_THROUGH      0b00001000
// supervisor bit. If the bit is set, then the page may be accessed all
// If the bit is not set, however only the supervisor can access it
#define PAGING_ACCESS_FROM_ALL      0b00000100
#define PAGING_IS_WRITEABLE             0b00000010
#define PAGING_IS_PRESENT                 0b00000001

#define PAGING_TOTAL_ENTRIES_PER_TABLE 1024
#define PAGING_PAGE_SIZE    4096

struct paging_4gb_chunk {
    uint32_t* directory_entry;
};
uint32_t* paging_4gb_chunk_get_directory(struct paging_4gb_chunk* chunk);
struct paging_4gb_chunk* paging_new_4gb(uint32_t flags);

void paging_switch(uint32_t* directory);
void enable_paging();

#endif //AGNETAOS_PAGING_H
