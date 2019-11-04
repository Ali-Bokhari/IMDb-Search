#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binary.h"

struct node* add_node(struct node* node, char* key, void *structure)
{
    if (node == NULL){
      struct node *nnode = malloc(sizeof(struct node));
      nnode->key = key;
      nnode->data = structure;
      nnode->child[0] = NULL;
      nnode->child[1] = NULL;
      return nnode;
    }
    if ( strcmp (key, node->key) < 0 )
        node->child[0]  = add_node(node->child[0], key, structure);
    else if (strcmp (key,  node->key) >= 0)
        node->child[1] = add_node(node->child[1], key, structure);
    return node;
}

struct node* find_node(struct node* root, char* key)
{
  if (root == NULL){
    return NULL;
  }
  if ( strcmp (key, root->key) < 0 )
      return find_node(root->child[0], key);
  else if (strcmp (key,  root->key) > 0)
      return find_node(root->child[1], key);
  return root;
}

void print_tree (struct node* root) {
  if (root == NULL) {
    return;
  }
  printf("%s\n",root->key);
  print_tree(root->child[0]);
  print_tree(root->child[1]);
}
