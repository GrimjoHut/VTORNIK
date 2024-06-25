#include "clear_state.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_date(const char *date_str, int *day, int *month, int *year) {
    if (sscanf(date_str, "%2d.%2d.%4d", day, month, year) != 3) {
        return 0;
    }
    if (*day < 1 || *day > 31 || *month < 1 || *month > 12 || *year < 1) {
        return 0;
    }
    return 1;
}

int date_compare(int day1, int month1, int year1, int day2, int month2, int year2) {
    if (year1 != year2)
        return year1 - year2;
    if (month1 != month2)
        return month1 - month2;
    return day1 - day2;
}

void clear_interval(const char *file_path, const char *start_date_str, const char *end_date_str) {
    int start_day, start_month, start_year;
    int end_day, end_month, end_year;

    if (!parse_date(start_date_str, &start_day, &start_month, &start_year) ||
        !parse_date(end_date_str, &end_day, &end_month, &end_year)) {
        printf("n/a\n");
        return;
    }

    FILE *file = fopen(file_path, "rb+");
    if (!file) {
        printf("n/a\n");
        return;
    }

    FILE *temp_file = fopen("temp.bin", "wb");
    if (!temp_file) {
        printf("n/a\n");
        fclose(file);
        return;
    }

    Record record;
    int records_deleted = 0;
    while (read_record(file, &record)) {
        if (date_compare(record.day, record.month, record.year, start_day, start_month, start_year) < 0 ||
            date_compare(record.day, record.month, record.year, end_day, end_month, end_year) > 0) {
            if (write_record(temp_file, &record) != 1) {
                printf("n/a\n");
                fclose(file);
                fclose(temp_file);
                remove("temp.bin");
                return;
            }
        } else {
            records_deleted++;
        }
    }

    fclose(file);
    fclose(temp_file);

    if (records_deleted == 0) {
        printf("n/a\n");
        remove("temp.bin");
        return;
    }

    if (remove(file_path) != 0 || rename("temp.bin", file_path) != 0) {
        printf("n/a\n");
        return;
    }

    printf("Records deleted: %d\n", records_deleted);
}

int main() {
    char file_path[256];
    char start_date[11], end_date[11];

    printf("Enter file path: ");
    scanf("%255s", file_path);
    printf("Enter date interval (DD.MM.YYYY DD.MM.YYYY): ");
    scanf("%10s %10s", start_date, end_date);

    clear_interval(file_path, start_date, end_date);
    return 0;
}
