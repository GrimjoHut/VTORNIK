#ifndef STATE_SORT_H
#define STATE_SORT_H

#include <stdio.h>  // добавляем включение stdio.h для использования типа FILE

typedef struct {
    int year, month, day, hour, minute, second, status, code;
} Record;

int read_record(FILE *file, Record *record);
int write_record(FILE *file, const Record *record);
int seek_record(FILE *file, long record_index);
int compare_records(const void *a, const void *b);
#endif
