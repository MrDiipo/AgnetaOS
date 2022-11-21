
#ifndef AGNETAOS_STRING_H
#define AGNETAOS_STRING_H
#include <stdbool.h>

char toLower(char s1);

int strlen(const char* ptr);
int strnlen(const char* ptr, int max);

bool isDigit(char c);
char* strcpy (char* dest, const char* src);

int strncmp(const char* s1, const char* s2, int n);
int to_numeric_digit (char c);

// compares the s1 and s2 by ignoring the cases
int istrncmp(const char* s1, const char* s2, int n);

int strnlen_terminator(const char* str, int max, char terminator);

char* strncpy(char* destination, const char* source, size_t num);
#endif //AGNETAOS_STRING_H
