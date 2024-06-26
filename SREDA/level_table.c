#include "shared.h"
#include <stdio.h>

// Additional functionalities for levels table
void print_level(Level *level) {
    printf("Memory Level: %d\n", level->memory_level);
    printf("Number of Cells: %d\n", level->num_cells);
    printf("Protection Flag: %d\n", level->protection_flag);
}
