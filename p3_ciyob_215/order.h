#ifndef ORDER
#define ORDER

typedef struct order {
	char * name;
	list * order_list;
  	struct order * next_order;
} order;

#endif
