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

struct title_principals_array* get_principals(char * path);
void build_pncindex( struct title_principals_array* principals );
struct title_principals * find_principals_nconst (struct title_principals_array* principals, char *key);
void build_pntindex( struct title_principals_array* principals );
struct title_principals * find_principals_tconst (struct title_principals_array* principals, char *key);
