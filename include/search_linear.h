#ifndef SEARCH_LINEAR_H
#define SEARCH_LINEAR_H

#include "index.h"

typedef struct btree {
    struct btree *left;
    struct btree *right;
    vec_id_t vec_id;
    unsigned int distance;
} btree_t;

int init_btree(vec_id_t vec_id, unsigned int distance, btree_t **node_out);
int destory_tree(btree_t *root);
void display_tree(btree_t *root);

int insert(btree_t **root, vec_id_t vec_id, unsigned int distance,
           btree_t **node_out);
int remove_furthest(btree_t *root, btree_t **new_root);
void flatten(btree_t *root, vec_id_t *arr_out);

int distance(vec_t vec_a, vec_t vec_b, unsigned int dimensions);

#endif
