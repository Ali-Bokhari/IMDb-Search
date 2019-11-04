struct title_basics {
  char * tconst;
  char * primaryTitle;
};

struct title_basics_array {
  int num;
  struct title_basics *titles;
  struct node *tconst_tree;
  struct node *primaryTitle_tree;
};

struct title_basics_array* get_title(char * path);
void build_ptindex( struct title_basics_array* titles );
struct title_basics * find_primary_title (struct title_basics_array* titles, char *key);
