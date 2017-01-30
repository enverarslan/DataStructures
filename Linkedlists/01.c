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
  root->data = 10;
  root->next = (node *) malloc(sizeof(node));
  /* Second Node Allocation */
  root->next->data = 20;
  root->next->next = (node *) malloc(sizeof(node));
  /* Third Node Allocation */
  root->next->next->data = 30;
  root->next->next->next = NULL;

  showList(root);
  return 0;
}

/*
-- Resulted as --
#1. node, data: 10 at pointed: 00031738, and points to 00031768
#2. node, data: 20 at pointed: 00031768, and points to 00031778
#3. node, data: 30 at pointed: 00031778, and points to 00000000
*/
