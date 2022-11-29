
#ifndef AGNETAOS_KERNEL_H
#define AGNETAOS_KERNEL_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 20

#define AGNETAOS_MAX_PATH  108

void print(const char* str);
void panic(const char* msg);
void kernel_main();

void kernel_page();
void kernel_registers();

#define ERROR(value) (void*)(value)
#define ERROR_I(value) (int)(value)
#define ISERR(value) ((int)value < 0)

#endif //AGNETAOS_KERNEL_H
