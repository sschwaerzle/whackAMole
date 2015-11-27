#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#define HOLES 16
#define MAXVAL 65536
#define SET(a, x) (a |= 1 << x)
#define TOGGLE(a, x) (a ^= 1 << x)

extern void enqueue(unsigned short number);
extern unsigned short dequeue();
