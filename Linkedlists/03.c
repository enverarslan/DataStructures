#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node * previous;
    struct node * next;
} node;

void showList(node *);
node * addItem(node *, int);
node * removeItem(node *);

/* Print Linked list values */
void showList(node * list){
    int i = 1;
    while( list != NULL){
        printf("#%d. node, data: %d at pointed: %p, and points to %p and previous item %p\n", i, list->data, list, list->next, list->previous);
        list = list->next;
        i++;
    }
}

/**
 * Create new list item after given list item
 * @param node * item
 * @param int data
 * @return node *
 */
node * addItem(node * item, int data){

    node * newItem = (node *) malloc(sizeof(node));
    newItem->data = data;
    newItem->previous = item;
    newItem->next = NULL;
    item->next = newItem;

    return newItem;
}

/**
 * Remove item and returns near last item (after or before).
 * @param node * item
 * @return node *
 */
node * removeItem(node * item){

    node * near;
    // first item deletion
    if(item->next != NULL && item->previous == NULL){
        item->next->previous = NULL;
        near = item->next;
    }
    // Middle item deletion
    else if(item->next != NULL && item->previous != NULL){
        item->next->previous = item->previous;
        item->previous->next = item->next;
        near = item->next;
    }
    // last item deletion
    else if(item->next == NULL && item->previous != NULL){
        item->previous->next = NULL;
        near = item->previous;
    }
    // there are no more linkedlist elements, print error and exit.
    else{
        printf("There is no previous and next item for relationship.");
        exit(-1);
    }
    free(item);
    return near;
}

int main(){

    node * root;
    node * iter;
    int i;

    // Create root item.
    root = (node *) malloc(sizeof(node));
    root->data = 0;
    root->previous = NULL;
    root->next = NULL;

    // Starts with root.
    iter = root;

    printf("----------\nAdd linkedlist items and print:\n----------\n");

    for (i = 1; i < 10; ++i) {
        iter = addItem(iter, i);
    }

    showList(root);

    printf("----------\nRemove odds items in list and print\n----------\n");

    // Starts with root again.
    iter = root;

    for (i = 0; i < 10; ++i) {
        // If item data is odd remove this item else go to next item else if there is no next item break and stop.
        if(iter->data % 2 == 1){
            iter = removeItem(iter);
        }else if(iter->next != NULL){
            iter = iter->next;
        }else{
            break;
        }
    }

    showList(root);

    printf("----------\n");

    return 0;
}

/*
-- Resulted as --
----------
Add linkedlist items and print:
----------
#1. node, data: 0 at pointed: 006E1A28, and points to 006E1A40 and previous item 00000000
#2. node, data: 1 at pointed: 006E1A40, and points to 006E1A58 and previous item 006E1A28
#3. node, data: 2 at pointed: 006E1A58, and points to 006E1AB8 and previous item 006E1A40
#4. node, data: 3 at pointed: 006E1AB8, and points to 006E1AD0 and previous item 006E1A58
#5. node, data: 4 at pointed: 006E1AD0, and points to 006E1AE8 and previous item 006E1AB8
#6. node, data: 5 at pointed: 006E1AE8, and points to 006E1B00 and previous item 006E1AD0
#7. node, data: 6 at pointed: 006E1B00, and points to 006E1770 and previous item 006E1AE8
#8. node, data: 7 at pointed: 006E1770, and points to 006E1788 and previous item 006E1B00
#9. node, data: 8 at pointed: 006E1788, and points to 006E17A0 and previous item 006E1770
#10. node, data: 9 at pointed: 006E17A0, and points to 00000000 and previous item 006E1788
----------
Remove odds items in list and print
----------
#1. node, data: 0 at pointed: 006E1A28, and points to 006E1A58 and previous item 00000000
#2. node, data: 2 at pointed: 006E1A58, and points to 006E1AD0 and previous item 006E1A28
#3. node, data: 4 at pointed: 006E1AD0, and points to 006E1B00 and previous item 006E1A58
#4. node, data: 6 at pointed: 006E1B00, and points to 006E1788 and previous item 006E1AD0
#5. node, data: 8 at pointed: 006E1788, and points to 00000000 and previous item 006E1B00
----------
*/