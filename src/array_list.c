#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "array_list.h"
#include "common.h"

struct list_t {
    unsigned int capacity;
    unsigned int length;
    size_t item_size;
    void *arr;
};

int create_list(unsigned int capacity, size_t item_size, list_t **list_out) {
    list_t *list = malloc(sizeof(list_t));
    if (list == NULL) {
        perror("malloc");
        return STATUS_ERROR;
    }

    list->capacity = capacity;
    list->length = 0;
    list->item_size = item_size;
    list->arr = calloc(capacity, item_size);
    if (list->arr == NULL) {
        perror("malloc");
        return STATUS_ERROR;
    }

    *list_out = list;

    return STATUS_SUCCESS;
}

int destroy_list(list_t *list) {
    free(list->arr);
    free(list);

    return STATUS_SUCCESS;
}

unsigned int get_capacity(list_t *list) {
    return list->capacity;
}

unsigned int get_length(list_t *list) {
    return list->length;
}

void *get_item(list_t *list, int index) {
    if (list->length == index) {
        return NULL;
    }

    return (char*)list->arr + index * list->item_size;
}

int add_item(list_t *list, void *item) {
    if (list->length == list->capacity) {
        if (realloc(list->arr, list->capacity *= GROW_FACTOR) == NULL) {
            perror("realloc");
            destroy_list(list);

            return STATUS_ERROR;
        }
    }

    memcpy((char*)list->arr + list->length * list->item_size, item, list->item_size);
    list->length++;

    return STATUS_SUCCESS;
}



