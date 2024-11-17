//
// Created by Barry Walker on 11/11/24.
//

#ifndef HEADERHACK_H
#define HEADERHACK_H

#endif //HEADERHACK_H

#ifdef __CLION_IDE__
static void *memset(void *ptr, const int value, const size_t num) {
    unsigned char *p = ptr;
    for (size_t i = 0; i < num; i++) {
        p[i] = (unsigned char) value;
    }
    return ptr;
}
#else
#include <string.h>  // Use the Amiga-specific memset macro here
#endif
