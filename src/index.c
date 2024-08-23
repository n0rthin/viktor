#include "index.h"
#include "array_list.h"
#include "common.h"
#include "search_linear.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct index_t {
    unsigned int dimensions;
    unsigned int size;
    list_t *vec_list;
};

int create_index(unsigned int dimensions, index_t **index_out) {
    index_t *index = malloc(sizeof(index_t));
    if (index == NULL) {
        perror("malloc");
        return STATUS_ERROR;
    }

    index->dimensions = dimensions;
    index->size = 0;

    if (create_list(1000, sizeof(vec_elem_t), &index->vec_list) ==
        STATUS_ERROR) {
        printf("Failed to initialize vector list");
        return STATUS_ERROR;
    }

    *index_out = index;

    return STATUS_SUCCESS;
}

int destroy_index(index_t *index) {
    destroy_list(index->vec_list);
    free(index);

    return STATUS_SUCCESS;
}

void display_index(index_t *index) {
    printf("[index]: %d vectors, %d dimensions\n", index->size,
           index->dimensions);
    int j = 0;
    for (int i = 0; i < index->size; i++) {
        printf("%d. [", i);
        for (j = 0; j < index->dimensions; j++) {
            printf("%d", *get_vec_elem(index, i, j));
            if (j < index->dimensions - 1) {
                printf(",");
            }
        }
        printf("]\n");
    }
}

unsigned int get_dimensions(index_t *index) { return index->dimensions; }

unsigned int get_size(index_t *index) { return index->size; }

vec_id_t add_vector(index_t *index, vec_t vec) {
    if (add_items(index->vec_list, vec, index->dimensions) == STATUS_ERROR) {
        return STATUS_ERROR;
    }

    return index->size++;
}

vec_elem_t *get_vec_elem(index_t *index, vec_id_t vec_id,
                         unsigned int elem_index) {
    int real_el_index = vec_id * index->dimensions + elem_index;
    return (vec_elem_t *)(get_item(index->vec_list, real_el_index));
}

int search_knn(index_t *index, vec_t qvec, unsigned int k,
               vec_id_t **result_out) {
    btree_t *tree = NULL;
    int dimensions = index->dimensions;
    int dist = 0;
    int tree_size = 0;

    printf("[index]: iterating over %d vectors\n", index->size);
    for (vec_id_t vec_id = 0; vec_id < index->size; vec_id++) {
        printf("[index]: calculating distance to %d vec\n", vec_id);
        dist = 0;
        for (int i = 0; i < dimensions; i++) {
            vec_elem_t vec_elem = *(get_vec_elem(index, vec_id, i));
            dist += pow(qvec[i] - vec_elem, 2);
        }

        if (insert(&tree, vec_id, dist, NULL) == STATUS_ERROR) {
            printf("failed to insert vector into search tree\n");
            destory_tree(tree);
            return STATUS_ERROR;
        }
        printf("Tree after insert:\n");
        display_tree(tree);
        printf("\n\n");

        tree_size++;
        if (tree_size > k) {
            if (remove_furthest(tree, &tree) == STATUS_ERROR) {
                printf("failed to remove furthest vector from search tree\n");
                destory_tree(tree);
                return STATUS_ERROR;
            }
            tree_size--;
            printf("Tree after removing furthest vector:\n");
            display_tree(tree);
            printf("\n\n");
        }
    }

    vec_id_t *vec_ids = calloc(tree_size, sizeof(vec_id_t));
    if (vec_ids == NULL) {
        perror("calloc");
        destory_tree(tree);
        return STATUS_ERROR;
    }
    flatten(tree, vec_ids);
    *result_out = vec_ids;

    return tree_size;
}
