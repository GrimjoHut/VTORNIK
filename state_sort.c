#include "state_sort.h"
#include <stdio.h>
#include <stdlib.h>

void print_record(const Record *record) {
    printf("%d %d %d %d %d %d %d %d\n", 
           record->year, record->month, record->day, 
           record->hour, record->minute, record->second, 
           record->status, record->code);
}

void print_file_contents(FILE *file) {
    Record record;
    rewind(file);
    while (read_record(file, &record)) {
        print_record(&record);
    }
}

void sort_file(FILE *file) {
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    long record_count = file_size / sizeof(Record);

    Record *records = malloc(record_count * sizeof(Record));
    if (records == NULL) {
        printf("n/a\n");
        return;
    }
    rewind(file);
    fread(records, sizeof(Record), record_count, file);
    qsort(records, record_count, sizeof(Record), compare_records);
    rewind(file);
    fwrite(records, sizeof(Record), record_count, file);
    free(records);
}

void add_record(FILE *file) {
    Record new_record;
    printf("Введите данные новой записи (year month day hour minute second status code):\n");
    if (scanf("%d %d %d %d %d %d %d %d", 
              &new_record.year, &new_record.month, &new_record.day, 
              &new_record.hour, &new_record.minute, &new_record.second, 
              &new_record.status, &new_record.code) != 8) {
        printf("n/a\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    if (write_record(file, &new_record) != 1) {
        printf("n/a\n");
        return;
    }
    sort_file(file);
}

int main() {
    char file_path[256];
    printf("Введите имя файла: ");
    if (scanf("%255s", file_path) != 1) {
        printf("n/a\n");
        return 1;
    }

    FILE *file = fopen(file_path, "rb+");
    if (!file) {
        printf("n/a\n");
        return 1;
    }

    int choice;
    do {
        printf("Меню:\n");
        printf("0 - Вывести содержимое файла\n");
        printf("1 - Вывести отсортированное содержимое файла\n");
        printf("2 - Добавить запись и вывести отсортированное содержимое файла\n");
        printf("3 - Выход\n");
        printf("Выберите опцию: ");
        if (scanf("%d", &choice) != 1) {
            printf("n/a\n");
            break;
        }

        switch (choice) {
            case 0:
                print_file_contents(file);
                break;
            case 1:
                sort_file(file);
                print_file_contents(file);
                break;
            case 2:
                add_record(file);
                print_file_contents(file);
                break;
            case 3:
                break;
            default:
                printf("n/a\n");
        }
    } while (choice != 3);

    fclose(file);
    return 0;
}
