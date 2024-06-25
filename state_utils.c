#include "state_sort.h"
#include <stdio.h>
#include <stdlib.h>

int read_record(FILE *file, Record *record) {
    size_t result = fread(record, sizeof(Record), 1, file);
    return result == 1;
}

int write_record(FILE *file, const Record *record) {
    size_t result = fwrite(record, sizeof(Record), 1, file);
    return result == 1;
}

int seek_record(FILE *file, long record_index) {
    return fseek(file, record_index * sizeof(Record), SEEK_SET);
}


int compare_records(const void *a, const void *b) {
    Record *recordA = (Record *)a;
    Record *recordB = (Record *)b;

    if (recordA->year != recordB->year)
        return recordA->year - recordB->year;
    if (recordA->month != recordB->month)
        return recordA->month - recordB->month;
    if (recordA->day != recordB->day)
        return recordA->day - recordB->day;
    if (recordA->hour != recordB->hour)
        return recordA->hour - recordB->hour;
    if (recordA->minute != recordB->minute)
        return recordA->minute - recordB->minute;
    return recordA->second - recordB->second;
}
