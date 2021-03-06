#include "floatscan.h"
#include "libc.h"
#include "shgetc.h"
#include "stdio_impl.h"
#include <stdlib.h>

static long double strtox(const char* s, char** p, int prec) {
    FILE f = {.buf = (void*)s, .rpos = (void*)s, .rend = (void*)-1, .lock = -1};
    shlim(&f, 0);
    long double y = __floatscan(&f, prec, 1);
    off_t cnt = shcnt(&f);
    if (p)
        *p = cnt ? (char*)s + cnt : (char*)s;
    return y;
}

float strtof(const char* restrict s, char** restrict p) {
    return strtox(s, p, 0);
}

double strtod(const char* restrict s, char** restrict p) {
    return strtox(s, p, 1);
}

long double strtold(const char* restrict s, char** restrict p) {
    return strtox(s, p, 2);
}
