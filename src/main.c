#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "array_list.h"
#include "index.h"
#include "common.h"

int test_list();

int main() {
    if (test_list() != 0) {
        return -1;
    }

    const int dimensionality = 10;
    index_t *index = NULL;
    if (create_index(dimensionality, &index) == STATUS_ERROR) {
        printf("failed to create index\n");
        return -1;
    }

    int *arr = calloc(dimensionality, sizeof(int));
    for (int i = 0; i < dimensionality; i++) {
        arr[i] = pow(i, i);
    }

    vec_id_t vec_id = add_vector(index, arr);
    if (vec_id == STATUS_ERROR) {
        printf("failed to add vector to index\n");
        return -1;
    }

    printf("vector id: %d\n", vec_id);
    printf("index size: %d\n", get_size(index));
    printf("elem of %d vector at index %d: %d\n", vec_id, 5, *get_vec_elem(index, vec_id, 5));


    return 0;
}

int test_list() {
    list_t *list = NULL;

    if (create_list(10, sizeof(int), &list) == STATUS_ERROR) {
        printf("failed to create list\n");
        return -1;
    }

    printf("Length: %d\n", get_length(list));
    printf("Capacity: %d\n", get_capacity(list));

    int *arr = calloc(20, sizeof(int));
    for (int i = 0; i < 20; i++) {
        arr[i] = i;

        if (add_item(list, &arr[i]) == STATUS_ERROR) {
            printf("failed to add %d item\n", 1);
            return -1;
        }
    }

    int *item_out = NULL;
    for (int i = 0; i < 20; i++) {
        if ((item_out = get_item(list, i)) == NULL) {
            printf("failed to get %d item\n", 1);
            return -1;
        }

        printf("Item at index %d: %d\n", i, *item_out);
    }

    printf("Length: %d\n", get_length(list));
    printf("Capacity: %d\n", get_capacity(list));

    destroy_list(list);

    return 0;
}
