#include "index.h"
#include "array_list.h"
#include "common.h"
#include "stdio.h"
#include "stdlib.h"

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
