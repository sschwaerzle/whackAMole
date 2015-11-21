#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#define HOLES 16
#define MAXVAL 65536

extern void enqueue(unsigned short number);
extern unsigned short dequeue();
