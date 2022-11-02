
#ifndef AGNETAOS_PAGING_H
#define AGNETAOS_PAGING_H

#define PAGING_CACHE_DISABLED        0b00010000
#define PAGING__WRITE_THROUGH      0b00001000
// supervisor bit. If the bit is set, then the page may be accessed all
// If the bit is not set, however only the supervisor can access it
#define PAGING_ACCESS_FROM_ALL      0b00000100
#define PAGING_IS_WRITEABLE             0b00000010
#define PAGING_IS_PRESENT                 0b00000001

#define PAGING_TOTAL_ENTRIES_PER_TABLE 1024

#endif //AGNETAOS_PAGING_H
