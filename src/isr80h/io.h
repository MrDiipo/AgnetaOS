
#ifndef AGNETAOS_IO_H
#define AGNETAOS_IO_H

struct interrupt_frame;

void* isr80h_command1_print(struct interrupt_frame* frame);
void* isr80h_command2_getkey(struct interrupt_frame* frame);
#endif //AGNETAOS_IO_H
