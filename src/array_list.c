#include "array_list.h"
#include "common.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list_t {
    unsigned int capacity;
    unsigned int length;
    size_t item_size;
    void *arr;
};

int calc_factor(int capacity, int length, int base_factor, int n);

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

unsigned int get_capacity(list_t *list) { return list->capacity; }

unsigned int get_length(list_t *list) { return list->length; }

void *get_item(list_t *list, int index) {
    // printf("[list]: accessing %dth item in the list of %d items\n", index, list->length);
    if (list->length == index) {
        return NULL;
    }

    return (char *)list->arr + index * list->item_size;
}

int add_item(list_t *list, void *item) {
    return add_items(list, item, 1);
}

int add_items(list_t *list, void *items, unsigned int n) {
    if (list->length + n > list->capacity) {
        int factor = calc_factor(list->capacity, list->length, GROW_FACTOR, n);
        if (realloc(list->arr, list->capacity *= factor) == NULL) {
            perror("realloc");
            destroy_list(list);

            return STATUS_ERROR;
        }
    }

    memcpy((char *)list->arr + list->length * list->item_size, items,
           list->item_size * n);
    list->length += n;

    return STATUS_SUCCESS;
}

int calc_factor(int capacity, int length, int base_factor, int n) {
    double ratio = ((double)length + (double)n) / (double)capacity;
    int power = ceil(log2(ratio) / log2((double)base_factor));

    return pow(base_factor, power);
}
