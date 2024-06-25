#ifndef STATE_SEARCH_H
#define STATE_SEARCH_H

#include <stdio.h>

typedef struct {
    int year, month, day, hour, minute, second, status, code;
} Record;

int read_record(FILE *file, Record *record);

void search_by_date(const char *file_path, const char *date_str);

#endif
