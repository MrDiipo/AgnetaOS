#include "string.h"

char toLower(char s1) {
    if (s1 >= 65 && s1 <= 90) {
        s1 += 32;
    }
    return s1;
}

int strlen(const char* ptr) {
    int i = 0;
    while (*ptr != 0) { // 0 is the value for ASCII NULL character
        i++;
        ptr += 1;
    }
    return i;
}

int strnlen(const char* ptr, int max) {
    int i = 0;
    for (i = 0; i < max; i++ ) {
        if (ptr[i] == 0) {
            break;
        }
    }
    return i;
}

int istrncmp(const char* s1, const char* s2, int n) {
    unsigned char u1, u2;
    while (n-- > 0) {
        u1 = (unsigned char )*s1++;
        u2 = (unsigned char)*s2++;
        if (u1 != u2 && toLower(u1) != toLower(u2)) {
            return u1 - u2;
        }
        if (u1 == '\0') return 0;
    }
    return 0;
}

int strncmp(const char* s1, const char* s2, int n) {
    unsigned char u1, u2;
    while(n-- > 0) {
        u1 = (unsigned char ) *s1++;
        u2 = (unsigned char ) *s2++;
        if (u1 != u2) {
            return u1 - u2;
        }
        if (u1 == '\0') {
            return 0;
        }
    }
    return 0;
}

// reads the string to find a null terminator or another specified terminator
int strnlen_terminator(const char* str, int max, char terminator) {
     int i = 0;
     for (i = 0; i < max, i++) {
         if (str[i] == '\0' || str[i] == terminator) break;
     }
    return i;
}

bool isDigit(char c) {
    return c >= 48 && c <= 57;
}

int to_numeric_digit (char c) {
    return c - 48;
}

char* strcpy (char* dest, const char* src) {
    char* res = dest;
    while (*src != 0) {
        *dest = *src;
        src += 1;
        dest += 1;
    }
    *dest = 0x00;
    return res;
}

// Function to implement `strncpy()` function
char* strncpy(char* destination, const char* source, size_t num) {
    // return if no memory is allocated to the destination
    if (destination == NULL) {
        return NULL;
    }

    // take a pointer pointing to the beginning of the destination string
    char* ptr = destination;

    // copy first `num` characters of C-string pointed by source
    // into the array pointed by destination
    while (*source && num--)
    {
        *destination = *source;
        destination++;
        source++;
    }

    // null terminate destination string
    *destination = '\0';

    // the destination is returned by standard `strncpy()`
    return ptr;
}
