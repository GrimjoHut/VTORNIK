// Структура для таблицы MODULES
typedef struct {
    int module_id;
    char module_name[30];
    int memory_level;
    int cell_number;
    int deletion_flag;
} MODULE;

// Структура для таблицы LEVELS
typedef struct {
    int memory_level;
    int cell_count;
    int protection_flag;
} LEVEL;

// Структура для таблицы STATUS_EVENTS
typedef struct {
    int event_id;
    int module_id;
    int new_status;
    char change_date[11];  // "dd.mm.yyyy\0" format
    char change_time[9];   // "hh:mm:ss\0" format
} STATUS_EVENT;
