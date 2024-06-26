#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULES "modules.dat"
#define MODULES_INDEX "modules.idx"

// Пример реализации функции добавления записи
int add_module(ENTITY *module) {
    FILE *db = fopen(MODULES, "rb+");
    if (db == NULL) {
        db = fopen(MODULES, "wb");
    }

    int result = insert(db, module, MODULES_INDEX);
    fclose(db);
    return result;
}

// Пример реализации функции удаления записи
int remove_module(int id) {
    FILE *db = fopen(MODULES, "rb+");
    if (db == NULL) {
        return -1;
    }

    int result = delete(db, id, MODULES_INDEX);
    fclose(db);
    return result;
}

// Пример реализации функции обновления записи
int modify_module(int id, ENTITY *module) {
    FILE *db = fopen(MODULES, "rb+");
    if (db == NULL) {
        return -1;
    }

    int result = update(db, id, module, MODULES_INDEX);
    fclose(db);
    return result;
}

// Пример реализации функции выбора записи
ENTITY *get_module(int id) {
    FILE *db = fopen(MODULES, "rb");
    if (db == NULL) {
        return NULL;
    }

    ENTITY *module = select(db, id, MODULES_INDEX);
    fclose(db);
    return module;
}
