#include "array_list.h"
#include "common.h"
#include "index.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int test_list();
#define DIMEN 2

int main() {
    if (test_list() != 0) {
        return -1;
    }

    const int dimensionality = DIMEN;
    index_t *index = NULL;
    if (create_index(dimensionality, &index) == STATUS_ERROR) {
        printf("failed to create index\n");
        return -1;
    }

    int vec1[DIMEN] = {1, 5};
    int vec2[DIMEN] = {1, 4};
    int vec3[DIMEN] = {3, 3};
    int vec4[DIMEN] = {3, 2};

    add_vector(index, vec2);
    add_vector(index, vec4);
    add_vector(index, vec3);
    add_vector(index, vec1);
    
    display_index(index);
    
    vec_id_t *search_result = NULL;
    vec_elem_t qvec[DIMEN] = {1, 6};
    int k = 2;
    int n_found = search_knn(index, qvec, k, &search_result);
    if (n_found == STATUS_ERROR) {
        printf("Failed to perform a search\n");
        return -1;
    }
    display_index(index);

    printf("Nearest %d neighbours to the [", k);
    for (int i = 0; i < DIMEN; i++) {
        printf("%d", qvec[i]);
        if (i < DIMEN - 1) {
            printf(",");
        }
    }
    printf("]:\n");

    for (int i = 0; i < n_found; i++) {
        printf("%d. [", search_result[i]);
        for (int j = 0; j < DIMEN; j++) {
            printf("%d", *get_vec_elem(index, search_result[i], j));
            if (j < DIMEN - 1) {
                printf(",");
            }
        }
        printf("]\n");
    }

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
