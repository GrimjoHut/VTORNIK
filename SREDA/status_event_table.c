#include "database.h"
#include <stdio.h>

// Additional functionalities for status events table
void print_status_event(StatusEvent *event) {
    printf("Event ID: %d\n", event->event_id);
    printf("Module ID: %d\n", event->module_id);
    printf("New Status: %d\n", event->new_status);
    printf("Change Date: %s\n", event->change_date);
    printf("Change Time: %s\n", event->change_time);
}
