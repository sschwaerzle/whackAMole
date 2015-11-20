#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "queue.h"

extern int readNextInt(FILE *fp);
extern void getNextConf(char hit, bool current[16], bool (*new)[16]);
extern unsigned short boolToShort(bool currentAr[16]);

