#include "util.h"

void memory_copy(char *source, char *dest, int nbyte) {
    int i;
    for (i = 0; i < nbyte; ++i) {
        dest[i] = source[i];
    }
}