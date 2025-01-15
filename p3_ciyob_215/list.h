#ifndef LIST
#define LIST

typedef struct item{
   char * item_name;
   struct item * next_item;
} item;

typedef struct {
   item * item;
} list;

#endif
