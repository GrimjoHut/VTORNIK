#ifndef CLEAR_STATE_H
#define CLEAR_STATE_H

#include <stdio.h>

typedef struct {
    int year, month, day, hour, minute, second, status, code;
} Record;

int read_record(FILE *file, Record *record);
int write_record(FILE *file, const Record *record);

#endif
