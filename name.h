struct name_basics {
  char * nconst;
  char * primaryName;
};

struct name_basics_array {
  int num;
  struct name_basics *names;
  struct node *nconst_tree;
  struct node *primaryName_tree;
};

struct name_basics_array* get_name(char * path);
void build_pnindex( struct name_basics_array* names );
struct name_basics * find_primary_name (struct name_basics_array* names, char *key);
void build_nindex( struct name_basics_array* names );
struct name_basics * find_nconst (struct name_basics_array* names, char *key);
