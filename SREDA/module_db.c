#include "database.h"
#include <stdio.h>
#include <stdlib.h>

void show_menu() {
    printf("1. View all active modules\n");
    printf("2. View all modules at the first memory level\n");
    printf("3. Add a module\n");
    printf("4. Delete a module\n");
    printf("5. Update a module\n");
    printf("6. Add a level\n");
    printf("7. Delete a level\n");
    printf("8. Update a level\n");
    printf("9. Add a status event\n");
    printf("10. Delete a status event\n");
    printf("11. Update a status event\n");
    printf("12. Exit\n");
}

int main() {
    FILE *db_modules = fopen("/materials/modules.db", "r+b");
    FILE *db_levels = fopen("/materials/levels.db", "r+b");
    FILE *db_status_events = fopen("/materials/status_events.db", "r+b");

    if (!db_modules || !db_levels || !db_status_events) {
        printf("Error opening database files\n");
        return 1;
    }

    int choice, id, level_number, event_id;
    Module module;
    Level level;
    StatusEvent event;

    while (1) {
        show_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                get_all_active_modules(db_modules);
                break;
            case 2:
                get_all_modules_at_first_level(db_modules);
                break;
            case 3:
                printf("Enter module details (ID Name MemoryLevel CellNumber DeletionFlag): ");
                scanf("%d %s %d %d %d", &module.module_id, module.module_name, &module.memory_level, &module.cell_number, &module.deletion_flag);
                insert_record(db_modules, &module, MODULES);
                break;
            case 4:
                printf("Enter module ID to delete: ");
                scanf("%d", &id);
                delete_record(db_modules, id, MODULES);
                break;
            case 5:
                printf("Enter module ID to update: ");
                scanf("%d", &id);
                printf("Enter new module details (ID Name MemoryLevel CellNumber DeletionFlag): ");
                scanf("%d %s %d %d %d", &module.module_id, module.module_name, &module.memory_level, &module.cell_number, &module.deletion_flag);
                update_record(db_modules, id, &module, MODULES);
                break;
            case 6:
                printf("Enter level details (MemoryLevel NumCells ProtectionFlag): ");
                scanf("%d %d %d", &level.memory_level, &level.num_cells, &level.protection_flag);
                insert_record(db_levels, &level, LEVELS);
                break;
            case 7:
                printf("Enter level number to delete: ");
                scanf("%d", &level_number);
                delete_record(db_levels, level_number, LEVELS);
                break;
            case 8:
                printf("Enter level number to update: ");
                scanf("%d", &level_number);
                printf("Enter new level details (MemoryLevel NumCells ProtectionFlag): ");
                scanf("%d %d %d", &level.memory_level, &level.num_cells, &level.protection_flag);
                update_record(db_levels, level_number, &level, LEVELS);
                break;
            case 9:
                printf("Enter status event details (EventID ModuleID NewStatus ChangeDate ChangeTime): ");
                scanf("%d %d %d %s %s", &event.event_id, &event.module_id, &event.new_status, event.change_date, event.change_time);
                insert_record(db_status_events, &event, STATUS_EVENTS);
                break;
            case 10:
                printf("Enter event ID to delete: ");
                scanf("%d", &event_id);
                delete_record(db_status_events, event_id, STATUS_EVENTS);
                break;
            case 11:
                printf("Enter event ID to update: ");
                scanf("%d", &event_id);
                printf("Enter new status event details (EventID ModuleID NewStatus ChangeDate ChangeTime): ");
                scanf("%d %d %d %s %s", &event.event_id, &event.module_id, &event.new_status, event.change_date, event.change_time);
                update_record(db_status_events, event_id, &event, STATUS_EVENTS);
                break;
            case 12:
                fclose(db_modules);
                fclose(db_levels);
                fclose(db_status_events);
                return 0;
        }
    }
}
