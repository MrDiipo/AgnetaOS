
#ifndef AGNETAOS_KERNEL_H
#define AGNETAOS_KERNEL_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 20

#define AGNETAOS_MAX_PATH  108

void print(const char* str);
void kernel_main();

#define ERROR(value) (void*)(value)
#define ERROR_I(value) (int)(value)
#define ISERR(value) ((int)value < 0)

#endif //AGNETAOS_KERNEL_H
