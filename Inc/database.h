#ifndef __DATABASE_H
#define __DATABASE_H

#include "stdint.h"

#define MAX_BUFFER_SIZE 500


typedef enum {STANDBY, PSV, PCV, ACV,SIMV} modes;
void print_debug(uint8_t *data, int size);

#endif
