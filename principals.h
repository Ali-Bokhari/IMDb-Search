struct title_principals {
  char * tconst;
  char * nconst;
  char * characters;
};

struct title_principals_array {
  int num;
  struct title_principals *principals;
  struct node *tconst_tree;
  struct node *nconst_tree;
};

struct title_principals_array* get_principal(char * path);
