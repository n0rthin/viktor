#include "search_linear.h"
#include "common.h"
#include "index.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int init_btree(vec_id_t vec_id, unsigned int distance, btree_t **tree_out) {
    btree_t *btree = malloc(sizeof(btree_t));
    if (btree == NULL) {
        perror("malloc");
        return STATUS_ERROR;
    }

    btree->vec_id = vec_id;
    btree->distance = distance;
    btree->left = NULL;
    btree->right = NULL;

    *tree_out = btree;

    return STATUS_SUCCESS;
}

int destory_tree(btree_t *node) {
    if (node == NULL) return STATUS_SUCCESS;

    if (node->left != NULL) {
        destory_tree(node->left);
    }

    if (node->right != NULL) {
        destory_tree(node->right);
    }

    free(node);
    return STATUS_SUCCESS;
}

void display_node(btree_t *node, int offset);
void display_tree(btree_t *root) {
    display_node(root, 0);
}

void display_node(btree_t *node, int offset) {

    if (node->right != NULL) {
        display_node(node->right, offset+1);
    }
    for (int i = 0; i < offset; i++) {
        printf("    ");
    }
    printf("vec_id: %d, distance: %d\n", node->vec_id, node->distance);
    if (node->left != NULL) {
        display_node(node->left, offset+1);
    }
}

int insert(btree_t **curr_ptr, vec_id_t vec_id, unsigned int distance,
           btree_t **node_out) {
    btree_t *curr = *curr_ptr;
    if (curr == NULL) {
        if (init_btree(vec_id, distance, curr_ptr) == STATUS_ERROR) {
            printf("failed to insert node to a btree\n");
            return STATUS_ERROR;
        }

        if (node_out != NULL) {
            *node_out = curr;
        }

        return STATUS_SUCCESS;
    }

    if (curr->distance < distance) {
        return insert(&curr->right, vec_id, distance, node_out);
    } else {
        return insert(&curr->left, vec_id, distance, node_out);
    }

    return STATUS_SUCCESS;
}

int remove_furthest(btree_t *node, btree_t **new_root) {
    if (node->right == NULL) {
        *new_root = node->left;
        free(node);
        return STATUS_SUCCESS;
    } else if (node->right->right == NULL) {
        return remove_furthest(node->right, &node->right);
    } else {
        return remove_furthest(node->right, new_root);
    }
}

void _flatten(btree_t *root, vec_id_t *arr_out, int *curr_idx);
void flatten(btree_t *root, vec_id_t *arr_out) {
    int curr_idx = 0;
    return _flatten(root, arr_out, &curr_idx);
}

void _flatten(btree_t *node, vec_id_t *arr_out, int *curr_idx) {
    if (node->left != NULL) {
        _flatten(node->left, arr_out, curr_idx);
    }

    arr_out[*curr_idx] = node->vec_id;
    (*curr_idx)++;

    if (node->right != NULL) {
        _flatten(node->right, arr_out, curr_idx);
    }
}

int distance(vec_t vec_a, vec_t vec_b, unsigned int dimensions) {
    int dist = 0;
    for (int i = 0; i < dimensions; i++) {
        dist += pow(vec_a[i] - vec_b[i], 2);
    }

    return dist;
}
