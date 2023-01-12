
#ifndef AGNETAOS_PROCESS_H
#define AGNETAOS_PROCESS_H

#include <stdint.h>
#include "../config.h"
#include "task.h"
#include "../loader/formats/elfloader.h"

#define PROCESS_FILETYPE_ELF 0
#define PROCESS_FILETYPE_BINARY 1

typedef unsigned char PROCESS_FILETYPE;

struct process {
    // The process id
    uint16_t id;
    char filename[AGNETAOS_MAX_PATH];

    // The main process task
    struct task* task;

    // The memory (malloc) allocations of the process
    void* allocations[AGNETAOS_MAX_PROGRAM_ALLOCATIONS];

    PROCESS_FILETYPE  filetype;

    union {
        // The physical pointer to the process memory
        // This assumes
        void *ptr;
        struct elf_file* elf_file;
    };

    // The physical pointer to the stack memory
    uint32_t stack;

    // The size of data pointed to by "ptr"
    uint32_t  size;

    struct keyboard_buffer {
        char buffer[AGNETAOS_KEYBOARD_BUFFER_SIZE];
        int tail;
        int head;
    } keyboard;
};

struct process *process_current();
int process_get(int process_id);

int process_switch(struct process* process);

int process_load_for_slot(const char *filename, struct process **process, int process_slot);
int process_load_switch(const char* filename, struct  process** process);
int process_load(const char* filename, struct process** process);
#endif //AGNETAOS_PROCESS_H
