#include <stdio.h>
#include <stdlib.h>

typedef struct n
{
  int data;
  struct n * next;
} node;

/* Print Linked list values */
void showList(node * list){
  int i = 1;
  while( list != NULL){
    printf("#%d. node, data: %d at pointed: %p, and points to %p\n", i, list->data, list, list->next);
    list = list->next;
    i++;
  }
}

int main(){

  node * root;
  /* First Node Allocation */
  root = (node *) malloc(sizeof(node));
  root->data = 0;
  root->next = NULL;
  /* Create another 9 nodes in the list. */
  node * iter = root;
  for(int i = 1; i < 10; i++){
    iter->next = (node *) malloc(sizeof(node));
    iter = iter->next;
    iter->data = i*10;
    iter->next = NULL;
  }
  showList(root);
  return 0;
}

/*
-- Resulted as --
#1. node, data: 0 at pointed: 00541738, and points to 00541768
#2. node, data: 10 at pointed: 00541768, and points to 00541778
#3. node, data: 20 at pointed: 00541778, and points to 00541788
#4. node, data: 30 at pointed: 00541788, and points to 00541798
#5. node, data: 40 at pointed: 00541798, and points to 005417A8
#6. node, data: 50 at pointed: 005417A8, and points to 005417B8
#7. node, data: 60 at pointed: 005417B8, and points to 005417C8
#8. node, data: 70 at pointed: 005417C8, and points to 005417D8
#9. node, data: 80 at pointed: 005417D8, and points to 005417E8
#10. node, data: 90 at pointed: 005417E8, and points to 00000000
*/
