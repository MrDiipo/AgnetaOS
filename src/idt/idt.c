#include "idt.h"
#include "../config.h"
#include "../memory/memory.h"
#include "../kernel.h"
#include "../io/io.h"

#include "../task/task.h"
#include "../status.h"

struct idt_desc idt_descriptors[AGNETAOS_TOTAL_INTERRUPTS];
struct idtr_desc idtr_descriptor;

extern void* interrupt_pointer_table[AGNETAOS_MAX_INTERRUPTS];

static INTERRUPT_CALLBACK_FUNCTION interrupt_callbacks[AGNETAOS_TOTAL_INTERRUPTS];
static ISR80H_COMMAND isr80h_commands[AGNETAOS_MAX_ISR80H_COMMANDS];

extern void idt_load(struct idtr_desc* ptr);
extern void init21h();
extern void no_interrupt();
extern void isr80h_wrapper();

void no_interrupt_handler() {

    outb(0x20, 0x20);
}

void interrupt_handler(int interrupt, struct interrupt_frame* frame) {
    kernel_page();
    if (interrupt_callbacks[interrupt] != 0 ) {
        task_current_save_state(frame);
        interrupt_callbacks[interrupt](frame);
    }
    task_page();
    outb(0x20, 0x20);
}

void idt_zero() {
    print("Divide by zero error\n");
}

void idt_set(int interrupt_no, void* address) {
    struct idt_desc* desc = &idt_descriptors[interrupt_no];
    desc->offset_1 = (uint32_t) address & 0x0000ffff;
    desc->selector = KERNEL_CODE_SELECTOR;
    desc->zero = 0x00;
    desc->type_attr = 0xEE;
    desc->offset_2 = (uint32_t) address >> 16;
}

// initialize interrupt vector table
void idt_init() {
    memset(idt_descriptors, 0, sizeof (idt_descriptors));
    idtr_descriptor.limit = sizeof (idt_descriptors) - 1;
    idtr_descriptor.base =  (uint32_t) idt_descriptors;

    for(int i = 0; i < AGNETAOS_TOTAL_INTERRUPTS; i++) {
        idt_set(i, interrupt_pointer_table[i]);
    }

    idt_set(0, idt_zero);
    idt_set(0x80, isr80h_wrapper);

    // Load the interrupt descriptor table
    idt_load(&idtr_descriptor);
}

int idt_register_interrupt_callback(int interrupt, INTERRUPT_CALLBACK_FUNCTION interrupt_callback) {
    if (interrupt < 0 || interrupt >= AGNETAOS_TOTAL_INTERRUPTS) {
        return  -EINVARG;
    }
    interrupt_callbacks[interrupt] = interrupt_callback;
    return 0;
}

void isr80h_register_command(int command_id, ISR80H_COMMAND command) {
    if (command_id < 0 || command_id >= AGNETAOS_MAX_ISR80H_COMMANDS) {
        panic("The command is out of bounds\n");
    }
    if (isr80h_commands[command_id]) {
        panic("You are attempting to overwrite an existing command");
    }
    isr80h_commands[command_id] = command;
}

void* isr80h_handle_command(int command, struct interrupt_frame* frame) {
    void* result = 0;

    if (command < 0 || command >= AGNETAOS_MAX_ISR80H_COMMANDS) {
        // invalid command
        return 0;
    }
    ISR80H_COMMAND command_func = isr80h_commands[command];
    if (!command_func) {
        // command does not exist
        return 0;
    }
    result = command_func(frame);
    return result;
}

void* isr80h_handler(int command, struct interrupt_frame* frame) {
    void* res = 0;
    kernel_page();
    task_current_save_state(frame);

    res = isr80h_handle_command(command, frame);
    task_page();
    return res;
}
