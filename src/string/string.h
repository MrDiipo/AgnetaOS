
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
int istrncmp(const char* s1, const char* s2, int n);

int strnlen_terminator(const char* str, int max, char terminator);
#endif //AGNETAOS_STRING_H
