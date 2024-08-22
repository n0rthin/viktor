#include <stdio.h>
#include <stdlib.h>
#include "array_list.h"
#include "common.h"

int main() {
    list_t *list = NULL;
    
    if (create_list(10, sizeof(int), &list) == STATUS_ERROR) {
        printf("failed to create list\n");
        return -1;
    }
    
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
