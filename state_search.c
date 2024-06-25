#include "state_search.h"
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

void search_by_date(const char *file_path, const char *date_str) {
    int target_day, target_month, target_year;
    if (!parse_date(date_str, &target_day, &target_month, &target_year)) {
        printf("n/a\n");
        return;
    }

    FILE *file = fopen(file_path, "rb");
    if (!file) {
        printf("n/a\n");
        return;
    }

    Record record;
    while (read_record(file, &record)) {
        if (record.day == target_day && 
            record.month == target_month && 
            record.year == target_year) {
            printf("%d\n", record.code);
            fclose(file);
            return;
        }
    }

    printf("n/a\n");
    fclose(file);
}

int main() {
    char file_path[256];
    char date_str[11];

    printf("Enter file path: ");
    scanf("%255s", file_path);
    printf("Enter date (DD.MM.YYYY): ");
    scanf("%10s", date_str);

    search_by_date(file_path, date_str);
    return 0;
}
