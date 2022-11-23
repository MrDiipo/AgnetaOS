#include "kernel.h"
#include <stdint.h>
#include <stddef.h>
#include "idt/idt.h"
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"
#include "disk/disk.h"
#include "string/string.h"
#include "fs/file.h"
#include "config.h"
#include "gdt/gdt.h"
#include "memory/memory.h"
#include "task/tss.h"

#include "task/task.h"
#include "task/process.h"
#include "status.h"

uint16_t* video_mem = 0;
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;

uint16_t terminal_make_char(char c, char colour) {
    return (colour << 8) | c;
}

void terminal_putchar(int x, int y, char c, char colour) {
    video_mem[(y * VGA_WIDTH) + x] = terminal_make_char(c, colour);
}

void terminal_writechar(char c, char colour) {

    if (c == '\n') {
        terminal_row += 1;
        terminal_col = 0;
    }

    terminal_putchar(terminal_col, terminal_row, c, colour);
    terminal_col += 1;
    if (terminal_col >= VGA_WIDTH) {
        terminal_col = 0;
        terminal_row += 1;
    }
}

// video memory algorithm
void terminal_initialize() {
    video_mem = (uint16_t*) (0xB8000);
    terminal_row = 0;
    terminal_col = 0;

    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            terminal_putchar(x, y, ' ', 0);
        }
    }
}

void print(const char* str) {
    size_t len = strlen(str);
    for (int i = 0; i < len; i++) {
        terminal_writechar(str[i], 15);
    }
}

static struct paging_4gb_chunk* kernel_chunk = 0;

void panic(const char* msg) {
    print(msg);
    while (1){}
}
struct tss tss;
struct gdt gdt_real[AGNETAOS_TOTAL_GDT_SEGMENTS];
struct gdt_structured gdt_structured[AGNETAOS_TOTAL_GDT_SEGMENTS] = {
        {.base = 0x00, .limit = 0x00, .type = 0x00}  ,   // NULL segment
        {.base = 0x00, .limit = 0xffffffff, .type = 0x9a}, // kernel code segment
        {.base = 0x00, .limit = 0xffffffff, .type = 0x92}, // Kernel dara segment
        {.base = 0x00, .limit = 0xffffffff, .type = 0xf8},      // User code segment
        {.base = 0x00, .limit = 0xffffffff, .type = 0xf2},      // User data segment
        {.base = (uint32_t)&tss, .limit = sizeof(tss), .type = 0xE9}, // TSS Segment
};
void kernel_main() {
    terminal_initialize();
    print("Hello world!\nTest!");

    memset(gdt_real, 0x00, sizeof(gdt_real));
    gdt_structured_to_gdt(gdt_real, gdt_structured, AGNETAOS_TOTAL_GDT_SEGMENTS);
    // Load the gdt
    gdt_load(gdt_real, sizeof(gdt_real));

    // initialize the heap
    kheap_init();

    // initialize file system
    fs_init();

    // search and initialize the disk
    disk_search_and_init();

    // initialize the interrupt descriptor table
    idt_init();

    // Setup the task switch segment (TSS)
    memset(&tss, 0x00, sizeof(tss));
    tss.esp0 = 0x600000; // where kernel stack is located
    tss.ss0 = KERNEL_DATA_SELECTOR;

    // Load the TSS
    tss_load(0x28);
    // setup paging
    kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);
    // switch to kernel paging chunk
    paging_switch(paging_4gb_chunk_get_directory(kernel_chunk));
    // enable paging
    enable_paging();

    struct process* process = 0;
    int res = process_load("0:/blank.bin", &process);
    if (res != AGNETAOS_ALL_OK) {
        panic("Failed to load blank.bin\n");
    }
    task_run_first_ever_task();

    while (1) {}
}
