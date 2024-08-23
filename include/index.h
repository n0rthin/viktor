#ifndef INDEX_H
#define INDEX_H

typedef struct index_t index_t;
typedef int vec_id_t;
typedef int vec_elem_t;
typedef vec_elem_t vec_t[];

int create_index(unsigned int dimensions, index_t **index_out);
int destroy_index(index_t *index);
void display_index(index_t *index);

unsigned int get_dimensions(index_t *index);
unsigned int get_size(index_t *index);

vec_id_t add_vector(index_t *index, vec_t vec);
vec_elem_t *get_vec_elem(index_t *index, vec_id_t vec_id,
                        unsigned int elem_index);

/**
 * If search was successful returns non-negative integer representing amount of
 * found neighbours. In case of error returns negative value
 */
int search_knn(index_t *index, vec_t qvec, unsigned int k,
               vec_id_t **result_out);

#endif
