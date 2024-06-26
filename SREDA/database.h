#ifndef SHARED_H
#define SHARED_H

#include <stdio.h>

typedef struct {
    int module_id;
    char module_name[30];
    int memory_level;
    int cell_number;
    int deletion_flag;
} Module;

typedef struct {
    int memory_level;
    int num_cells;
    int protection_flag;
} Level;

typedef struct {
    int event_id;
    int module_id;
    int new_status;
    char change_date[11]; // "dd.mm.yyyy\0"
    char change_time[9];  // "hh:mm:ss\0"
} StatusEvent;

typedef enum {
    MODULES,
    LEVELS,
    STATUS_EVENTS
} TableType;

void *select_record(FILE *db, int id, TableType tableType);
int insert_record(FILE *db, void *record, TableType tableType);
int delete_record(FILE *db, int id, TableType tableType);
int update_record(FILE *db, int id, void *record, TableType tableType);

void get_all_active_modules(FILE *db);
void get_all_modules_at_first_level(FILE *db);

#endif // SHARED_H
