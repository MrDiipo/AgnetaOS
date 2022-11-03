
#ifndef AGNETAOS_STRING_H
#define AGNETAOS_STRING_H
#include <stdbool.h>

int strlen(const char* ptr);
int strnlen(const char* ptr, int max);

bool isDigit(char c);

int to_numeric_digit (char c);
#endif //AGNETAOS_STRING_H
