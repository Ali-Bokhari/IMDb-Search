struct node {
  char * key;
  void * data;
  struct node *child[2];
};

struct node* add_node(struct node* node, char* key, void *structure);
struct node* find_node(struct node* node, char *key);
void print_tree (struct node* root);
