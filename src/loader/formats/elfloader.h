
#ifndef AGNETAOS_ELFLOADER_H
#define AGNETAOS_ELFLOADER_H

#include <stdint.h>
#include <stddef.h>

#include "elf.h"
#include "../../config.h"

struct elf_file {
    char filename[AGNETAOS_MAX_PATH];
    int in-memory_size;

    /**
     * The physical memory that this elf file is loaded at
     */
     void* elf_memory;

     /**
      * The virtual base address of this binary
      */
     void* virtual_base_address;

     /**
      * The ending virtual address
      */
     void* virtual_end_address;

     /**
      * The physical base address
      */
     void* physical_base_address;

     /**
      * The physical end address of this binary
      */
     void* physical_end_address;
};

#endif //AGNETAOS_ELFLOADER_H
