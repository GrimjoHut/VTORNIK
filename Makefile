CC = gcc
CFLAGS = -Wall -Wextra -O2

# Исходные файлы для state_sort
SRC_SORT = src/state_sort.c src/file_utils.c
TARGET_SORT = build/Quest_1

# Исходные файлы для state_search
SRC_SEARCH = src/state_search.c src/file_utils.c
TARGET_SEARCH = build/Quest_2

# Исходные файлы для clear_state
SRC_CLEAR = src/clear_state.c src/file_utils.c
TARGET_CLEAR = build/Quest_3

all: $(TARGET_SORT) $(TARGET_SEARCH) $(TARGET_CLEAR)

$(TARGET_SORT): $(SRC_SORT)
	$(CC) $(CFLAGS) -o $(TARGET_SORT) $(SRC_SORT)

$(TARGET_SEARCH): $(SRC_SEARCH)
	$(CC) $(CFLAGS) -o $(TARGET_SEARCH) $(SRC_SEARCH)

$(TARGET_CLEAR): $(SRC_CLEAR)
	$(CC) $(CFLAGS) -o $(TARGET_CLEAR) $(SRC_CLEAR)

clean:
	rm -f $(TARGET_SORT) $(TARGET_SEARCH) $(TARGET_CLEAR)
