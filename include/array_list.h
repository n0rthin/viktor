#ifndef LIST_H
#define LIST_H

#include <stddef.h>

#define GROW_FACTOR 2

typedef struct list_t list_t;

int create_list(unsigned int capacity, size_t item_size, list_t **list_out);
int destroy_list(list_t *list);

unsigned int get_capacity(list_t *list);
unsigned int get_length(list_t *list);
void *get_item(list_t *list, int index);
int add_item(list_t *list, void *item);

#endif
