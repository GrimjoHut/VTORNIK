#include "shared.h"
#include <stdlib.h>
#include <string.h>

// Common CRUD operations
void *select_record(FILE *db, int id, TableType tableType) {
    void *record;
    int record_size;

    switch (tableType) {
        case MODULES:
            record = malloc(sizeof(Module));
            record_size = sizeof(Module);
            break;
        case LEVELS:
            record = malloc(sizeof(Level));
            record_size = sizeof(Level);
            break;
        case STATUS_EVENTS:
            record = malloc(sizeof(StatusEvent));
            record_size = sizeof(StatusEvent);
            break;
        default:
            return NULL;
    }

    fseek(db, 0, SEEK_SET);
    while (fread(record, record_size, 1, db)) {
        int record_id = (tableType == MODULES) ? ((Module*)record)->module_id :
                        (tableType == LEVELS) ? ((Level*)record)->memory_level :
                        ((StatusEvent*)record)->event_id;

        if (record_id == id) {
            return record;
        }
    }
    free(record);
    return NULL;
}

int insert_record(FILE *db, void *record, TableType tableType) {
    int record_size = (tableType == MODULES) ? sizeof(Module) :
                      (tableType == LEVELS) ? sizeof(Level) :
                      sizeof(StatusEvent);

    fseek(db, 0, SEEK_END);
    return fwrite(record, record_size, 1, db);
}

int delete_record(FILE *db, int id, TableType tableType) {
    void *record = select_record(db, id, tableType);
    if (!record) return 0;

    if (tableType == MODULES) {
        ((Module*)record)->deletion_flag = 1;
    }

    int record_size = (tableType == MODULES) ? sizeof(Module) :
                      (tableType == LEVELS) ? sizeof(Level) :
                      sizeof(StatusEvent);

    fseek(db, -record_size, SEEK_CUR);
    int result = fwrite(record, record_size, 1, db);
    free(record);
    return result;
}

int update_record(FILE *db, int id, void *record, TableType tableType) {
    void *temp = select_record(db, id, tableType);
    if (!temp) return 0;
    free(temp);

    int record_size = (tableType == MODULES) ? sizeof(Module) :
                      (tableType == LEVELS) ? sizeof(Level) :
                      sizeof(StatusEvent);

    fseek(db, -record_size, SEEK_CUR);
    return fwrite(record, record_size, 1, db);
}

// Aggregation queries
void get_all_active_modules(FILE *db) {
    Module module;
    fseek(db, 0, SEEK_SET);
    while (fread(&module, sizeof(Module), 1, db)) {
        if (module.deletion_flag == 0) {
            printf("Module ID: %d, Name: %s, Memory Level: %d, Cell Number: %d\n",
                   module.module_id, module.module_name, module.memory_level, module.cell_number);
        }
    }
}

void get_all_modules_at_first_level(FILE *db) {
    Module module;
    fseek(db, 0, SEEK_SET);
    while (fread(&module, sizeof(Module), 1, db)) {
        if (module.memory_level == 1) {
            printf("Module ID: %d, Name: %s, Cell Number: %d\n",
                   module.module_id, module.module_name, module.cell_number);
        }
    }
}
