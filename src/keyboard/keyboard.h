
#ifndef AGNETAOS_KEYBOARD_H
#define AGNETAOS_KEYBOARD_H

struct  process;

typedef int (*KEYBOARD_INIT_FUNCTION)();

struct keyboard {
    KEYBOARD_INIT_FUNCTION init;
    char name[20];
    struct keyboard* next;
};

void keyboard_init();
void keyboard_backspace(struct  process* process);
int keyboard_insert(struct keyboard* keyboard);

void keyboard_push(char c);
char keyboard_pop();

#endif //AGNETAOS_KEYBOARD_H
