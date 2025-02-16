/*	Caleb Iyob, G01257159
 *	Lab Section 215
 *	Project 3
 */
#include "strcmpa.h"
#include "list.h"
#include "order.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void sorted_list(list*);
/*order *sorted_orders(order*);*/
order *make_order(char*);
void add_item(list*,item*);
int verifying_alpha(char*);
list *make_list();
item *make_item(char*);
order *add_order(order*,list*);
order *delete_order(order*);	/*Function prototypes, including the helper methods.*/
void display_order(order*);
void display_orders(order*);
void remove_item(list*,item*);
order *change_order(order*);
void transfer_order_items(order*, order*);
void merge_orders(order*);
void current_orders(order*);
int validate_menu(char[]);
void free_order(order*);
void take_off(char[]);
int main(){
	char c1[100];
	char useroption[50];		/*Choice the user makes at the menu*/
	order *orderlist=NULL;		/*This orderlist starts off as empty and gets updated with each function call*/		
	printf("Ruff! Welcome to Chiquito's Store!\n");
	while(1){
		printf("Woof! (Please choose an option from the menu below!):\n");
		printf("***** Order Options *****\n");
		printf("Add Order:	add or Add\n");
		printf("Delete Order:	delete or Delete\n");
		printf("Display Order:	display or Display\n");
		printf("Display Orders:	orders or Orders\n");
		printf("Change Order:	change or Change\n");
		printf("Merge Order:	merge or Merge\n");
		printf("Current Orders:	current or Current\n");
		printf("Exit:	exit or Exit\n");
		printf("Select an order option: \n");
		fgets(c1,100,stdin);
		sscanf(c1,"%s",useroption);
		while(validate_menu(useroption)!=0){
                         printf("Invalid option. Please re-enter a valid menu option.\n");
                         fgets(c1,100,stdin);
                         sscanf(c1,"%s",useroption);
                         validate_menu(useroption);
                }
		if(strcmp(useroption,"add")==0||strcmp(useroption,"Add")==0){
			list *empty_list=make_list();	/*creates an empty list of items to add an order to*/
			orderlist=add_order(orderlist,empty_list);
		}
		else if(strcmp(useroption,"delete")==0||strcmp(useroption,"Delete")==0){
			orderlist=delete_order(orderlist);
		}
		else if(strcmp(useroption,"display")==0||strcmp(useroption,"Display")==0){
			display_order(orderlist);
		}
		else if(strcmp(useroption,"orders")==0||strcmp(useroption,"Orders")==0){
			display_orders(orderlist);
		}
		else if(strcmp(useroption,"change")==0||strcmp(useroption,"Change")==0){
			orderlist=change_order(orderlist);
		}
		else if(strcmp(useroption,"merge")==0||strcmp(useroption,"Merge")==0){
			merge_orders(orderlist);
		}
		else if(strcmp(useroption,"current")==0||strcmp(useroption,"Current")==0){
			current_orders(orderlist);
		}
		else if(strcmp(useroption,"exit")==0||strcmp(useroption,"Exit")==0){
			free_order(orderlist);
			printf("Ruff! (Thanks for ordering! Goodbye!)\n");
			return 0;	
			break;
		}
	}
	return 0;
}
/*Checks for whether a valid input was inserted into the menu
 * Returns 1 if invalid, 0 if valid*/
int validate_menu(char useroption[]){
	int valid=0;
	if(strcmp(useroption,"add")!=0 && strcmp(useroption,"Add")!=0 && strcmp(useroption,"delete")!=0 && strcmp(useroption,"Delete")!=0 && strcmp(useroption,"display")!=0 && strcmp(useroption,"Display")!=0 && strcmp(useroption,"orders")!=0 && strcmp(useroption,"Orders")!=0 && strcmp(useroption,"change")!=0 && strcmp(useroption,"Change")!=0 && strcmp(useroption,"merge")!=0 && strcmp(useroption,"Merge")!=0 && strcmp(useroption,"current")!=0 && strcmp(useroption,"Current")!=0 && strcmp(useroption,"exit")!=0 && strcmp(useroption,"Exit")!=0){
		valid +=1;
	}
	return valid;
}
void free_order(order *orderlist){/*completely frees a list of orders from the ground up*/
	order *current_order;
	item *current_item;
	order *temp_order;
	item *temp_item;
	current_order=orderlist;
	while(current_order!=NULL){
		temp_order=current_order;
		current_item=current_order->order_list->item;
		while(current_item!=NULL){/*traverses through each list of items and frees them*/
			temp_item=current_item;
			current_item=current_item->next_item;
			free(temp_item->item_name);
			free(temp_item);/*frees item's fields before freeing the item itself*/
		}
		free(current_order->order_list);
		free(current_order->name);
		current_order=current_order->next_order;
		free(temp_order);/*frees each order's fields before the order itself*/
	}
}
order * make_order(char *ordername){/*makes an order through a name parameter*/
	order *created_order=(order*)malloc(sizeof(order));
	created_order->name=ordername;
	created_order->order_list=NULL;
	created_order->next_order=NULL;
	return created_order;
}

void add_item(list *itemlist,item *added_item){/*adds a given item into a list of items*/
	added_item->next_item=itemlist->item;
	itemlist->item=added_item;	
}

list *make_list(){/*initializes an empty list fully malloced*/
	list *example_list=(list*)malloc(sizeof(list));
	example_list->item=NULL;
	return example_list;
}
item * make_item(char *itemname){/*makes an item through a name parameter*/
	item * created_item=(item*)malloc(sizeof(item));
	created_item->next_item=NULL;
	created_item->item_name=itemname;
	return created_item;
}
void sorted_list(list *unsorted_list){
	item *head_item=unsorted_list->item;
	item *current_item;
	item *nextitem;
	item *prev_item;
	int flag=1;
	if(head_item==NULL||head_item->next_item==NULL){
		return;		
	}
	while(flag){
		flag=0;
		current_item=head_item;
        	nextitem=head_item->next_item;
        	prev_item=NULL;
		while(nextitem!=NULL){
			if(strcmpa(current_item->item_name,nextitem->item_name)>0){
				if(prev_item==NULL){
					current_item->next_item=nextitem->next_item;
					nextitem->next_item=current_item;
					head_item=nextitem;
					nextitem=current_item;
					current_item=head_item;
				}	
				else{
					prev_item->next_item=nextitem;
					current_item->next_item=nextitem->next_item;
                                	nextitem->next_item=current_item;
                                	nextitem=current_item;
					current_item=prev_item->next_item;
				}
				flag=1;
			}
			prev_item=current_item;
			current_item=nextitem;
			nextitem=nextitem->next_item;
		}
	}
	unsorted_list->item=head_item;
}
order *add_order(order *orderlist,list *itemlist){
	order *example_order;		/*order that later gets added into orderlist*/
	char c1[500];
	char c2[500];
	int flag=0;
	char *itemname=NULL;		/*name pointer for each item being added*/
	char *added_order_name=NULL;	/*name of the order being added into orderlist*/
	item *new_item;			/*item pointer used to create the items being added*/
	order *order_pointer;		/*order pointer used to traverse through orderlist and insert the order*/
	printf("Please enter the name on the order: \n");
	fgets(c1,sizeof(c1),stdin);
	while(verifying_alpha(c1)==0){
                fgets(c1,500,stdin);
                verifying_alpha(c1);
        }
	added_order_name=malloc(sizeof(char)*(strlen(c1)+1));
	sscanf(c1,"%[^\n]s",added_order_name);
	example_order=make_order(added_order_name);	/*assigns the order name from the user to example_order using a helper method*/
	while(flag!=1){
		printf("Please enter the item you would like to order: \n");
		fgets(c2,sizeof(c2),stdin);
		if(c2[0]=='\n'){
			flag+=1;		/*exits the loop if the user only inputs the enter key*/
		}
		else{
			while(verifying_alpha(c2)==0){
                        	fgets(c2,sizeof(c2),stdin);
                        	verifying_alpha(c2);
                	}
			itemname=malloc(sizeof(char)*(strlen(c2)+1));
                	sscanf(c2,"%[^\n]s",itemname);		/*assigns the valid user input to itemname*/
			new_item=make_item(itemname);		/*assigns new_item with the itemname using a helper method*/
			add_item(itemlist,new_item);		/*adds the newly created item into the given itemlist*/
		}
	}
	sorted_list(itemlist);			/*sorts the list of items alphabetically*/
	example_order->order_list=itemlist;		/*assigns itemlist to example_order's list of items*/
	if(orderlist==NULL){
		orderlist=example_order;	/*example_order becomes the sole order of the orderlist if it begins as null*/
	}
	else{
		order_pointer=orderlist;		/*order_pointer is being used to traverse through orderlist*/
		while(order_pointer->next_order!=NULL){		
			order_pointer=order_pointer->next_order;	
		}
		order_pointer->next_order=example_order;	/*example_order becomes the next order in the list if there is only one order, otherwise continuing until the next field becomes null*/
	}	
	printf("Arf! (Your order has been added!)\n");		/*print message indicating that the order has been added to the list*/
	printf("\n");
	return orderlist;				/*returns the updated orderlist with the new order added in*/
}

order *delete_order(order *orderlist){
	char order_name[500];			/*name of the order being deleted*/
	order *current_order=orderlist;		/*order pointer used to traverse through orderlist*/
	order *prev_order=NULL;			/*pointer to keep track of the previous order*/
	item *current_item;			/*item pointer to traverse through the given order's list of items*/
	item *temp_item;			/*temporary pointer to current_item*/
	order *temp_order;			/*temporary pointer to current_order*/
	printf("Please enter the name on the order: \n");
	fgets(order_name,500,stdin);
	while(verifying_alpha(order_name)==0){
                fgets(order_name,500,stdin);
                verifying_alpha(order_name);
        }
	take_off(order_name);			/*Helper function on order_name to take off trailing \n and whitespace*/
	while(current_order!=NULL){		/*traverses through the entire orderlist*/
		if(strcmp(order_name,current_order->name)==0){		/*Matching name verification*/
			current_item=current_order->order_list->item;	
			while(current_item!=NULL){			/*traverses through the current order's list of items*/ 
				temp_item=current_item;			
				current_item=current_item->next_item;	/*temp_item adopts current_item's values before current_item moves forward*/
				free(temp_item->item_name);
				free(temp_item);			/*temp_item's data is freed while current_item can continue to traverse*/
			}
			free(current_order->order_list);		
			free(current_order->name);		/*Mid-level freeing of current_order's list of items and its name*/
			if(prev_order==NULL){
				orderlist=orderlist->next_order;	/*assigns orderlist's head to its next order if it's the only order in the list*/
			}
			else{
				prev_order->next_order=current_order->next_order;	
			}
			temp_order=current_order;
			current_order=current_order->next_order;	/*temp_order adopts current_order's values before current_order moves forward*/
			free(temp_order);			/*temp_order pointing to the list's head is freed*/
		}
		else{
			prev_order=current_order;
                	current_order=current_order->next_order;	/*traverses through the orderlist until a name matches*/
		}
	}
	printf("Arf! (Your order has been deleted!)\n");	/*print message verifying the delete was successful*/
	printf("\n");
	return orderlist;			/*returns the updated orderlist after the designated order has been deleted*/
}

void display_order(order *orderlist){
	char order_name[500];
	int counter=1;		/*Counter for the number of items*/
	order *current_order=orderlist;		/*order pointer for traversing through orderlist*/
	item *current_item;			/*item pointer for traversing through a given order's list of items*/
	printf("Please enter the name on the order: \n");
	fgets(order_name,500,stdin);
	while(verifying_alpha(order_name)==0){
		fgets(order_name,500,stdin);
		verifying_alpha(order_name);
	}
	take_off(order_name);			/*take_off call for getting rid of trailing \n and whitespace in the order name*/
	while(current_order!=NULL){
		if(strcmp(order_name,current_order->name)==0){		/*name verification*/
			current_item=current_order->order_list->item;		
			printf("Displaying order(s) placed by %s:\n",order_name);
				while(current_item!=NULL){		/*traverses the item list using current_item*/
					printf("Item %d: %s\n",counter,current_item->item_name);
					counter++;			/*increments the counter for each item*/
					current_item=current_item->next_item;	/*moves current_item forward in the list*/
				}
		}
		current_order=current_order->next_order;	/*iterates through orderlist until it finds a name match*/
	}
	printf("\n");
}

void display_orders(order *orderlist){
	int itemcounter=0;
	order *current_order=orderlist;
	item *current_item;
        printf("Displaying all orders placed currently:\n");		
	while(current_order!=NULL){		/*traverses through orderlist until it reaches null*/
		printf("Order placed by %s:\n",current_order->name);	/*Header for each order in the list*/
		current_item=current_order->order_list->item;
		itemcounter=1;
		while(current_item!=NULL){
			printf("Item %d: %s\n",itemcounter,current_item->item_name);	/*prints out each item in every order*/
			itemcounter++;
			current_item=current_item->next_item;	/*current_item continues moving until it reaches null*/
		}
		current_order=current_order->next_order;
	}
	printf("\n");
}
void remove_item(list *itemlist, item *removed_item){/*helper method for removing a single item from a list of items*/
	item *current_item;
	item *prev_item;
	current_item=itemlist->item;
	prev_item=NULL;
	while(current_item!=NULL){
		if(strcmp(removed_item->item_name,current_item->item_name)==0){	/*Checks for a matching name with the item being removed*/
			if(prev_item==NULL){
				itemlist->item=current_item->next_item;	/*Bumps up the head of the itemlist if its previous item is null*/
			}
			else{
				prev_item->next_item=current_item->next_item;
			}
			free(current_item->item_name);		
			free(current_item);		/*Freeing current_item after freeing its name field*/
			break;				/*breaks out before removing anything else*/
		}
		prev_item=current_item;
		current_item=current_item->next_item;
	}
}
void take_off(char userinput[]){	/*helper function for getting rid of trailing \n and whitespace*/
	while(strlen(userinput)>0&&(userinput[strlen(userinput)-1]=='\n'||userinput[strlen(userinput)-1]==' ')){
                userinput[strlen(userinput)-1]='\0';
        }	
}
int verifying_alpha(char *received_name){/*helper method for verifying that all names of orders and items contain alphabetical characters*/
	int valid=1;
	int i;
	take_off(received_name);
	if(strlen(received_name)==0){
		return 0;
	}
	for(i=0;i<strlen(received_name);++i){
		if(isalpha(received_name[i])==0 && received_name[i]!=' '){/*will prompt the user to re-enter values that aren't alphabetical with the exception of whitespace in between*/
			printf("Invalid option. Please re-enter a name with alphabetical characters A-Z.\n");
			return 0;	
		}
	}
	return valid;
}
order *change_order(order *orderlist){
	char order_name[500];
	char item_action[500];
	char removed_item[500];
	char c4[500];
	char *included_item;
	char switched_item_name[500];
	char c5[500];
	char *replaced_item_name;
	item *current_item;
	order *current_order=orderlist;
	item *added_item;
	order *prev_order;
	item *temp_item;
	int removecount;
	removecount=0;
	prev_order=NULL;
	printf("Change order called.\n");
	printf("Please enter the name on the order: \n");	/*reads in the name of the order being changed*/
	fgets(order_name,500,stdin);
	while(verifying_alpha(order_name)==0){
                fgets(order_name,500,stdin);
                verifying_alpha(order_name);
        }
	take_off(order_name);	/*gets rid of trailing \n and whitespace*/
	while(current_order!=NULL){
                if(strcmp(order_name,current_order->name)==0){	/*name verification*/
			printf("Would you like to remove, include, or switch an item from your order? \n");
			fgets(item_action,500,stdin);	/*takes in the item action for removing, including, or switching*/
			while(verifying_alpha(item_action)==0){
                		fgets(item_action,500,stdin);
                		verifying_alpha(item_action);
        		}
			take_off(item_action);
			if(strcmp(item_action,"remove")==0||strcmp(item_action,"Remove")==0){
				printf("Please enter the item you would like to remove: \n");
				do{
					current_item=current_order->order_list->item;
					fgets(removed_item,500,stdin);	/*takes in the name of the item being removed*/
					while(verifying_alpha(removed_item)==0){
                				fgets(removed_item,500,stdin);
                				verifying_alpha(removed_item);
        				}
					take_off(removed_item);
					if(strcmp(removed_item,"back")==0||strcmp(removed_item,"Back")==0){
						break;
					}
					while(current_item!=NULL){/*traverses through the list of items until it finds a match*/
						if(strcmp(removed_item,current_item->item_name)==0){
							temp_item=current_item;
							current_item=current_item->next_item;	/*moves current_item forward before removing its temporary copy*/
							remove_item(current_order->order_list,temp_item);
							removecount++;	/*removecount increments whenever a successful removal occurs*/
						}
						else{
							current_item=current_item->next_item;
						}
					}
					if(removecount>0){
						if(current_order->order_list->item==NULL){/*Deletes the order if the item removed was the only item in the order*/
							if(prev_order==NULL){
								orderlist=orderlist->next_order;
							}
							else{
								prev_order->next_order=current_order->next_order;
							}
                                			free(current_order->order_list);
                                			free(current_order->name);
                                			free(current_order);	/*frees all of current_order's fields before freeing current_order*/
                                        	}
						printf("Ruff! (Removed an item from your order!)\n");
						printf("\n");
					}
					if(removecount==0){
						printf("Invalid option. Please re-enter an item that is in the list or type 'back' to return to the menu.\n");
					}
				}while(removecount==0);
			}
			else if(strcmp(item_action,"include")==0||strcmp(item_action,"Include")==0){
				current_item=current_order->order_list->item;
				printf("Please enter the item you would like to include: \n");
				fgets(c4,500,stdin);
				while(verifying_alpha(c4)==0){
                			fgets(c4,500,stdin);
                			verifying_alpha(c4);
        			}
				included_item=malloc(sizeof(char)*(strlen(c4)+1));
				sscanf(c4,"%[^\n]s",included_item);	/*assigns user input to included_item*/
				added_item=make_item(included_item);	/*makes an item with included_item's name as its parameter*/
				add_item(current_order->order_list,added_item);	/*adds the newly created item into the list*/
				sorted_list(current_order->order_list);	/*arranges the items alphabetically*/
				printf("Ruff! (Added an item to your order!)\n");
				printf("\n");
			}
			else if(strcmp(item_action,"switch")==0||strcmp(item_action,"Switch")==0){
				current_item=current_order->order_list->item;
				printf("Please enter the item you would like to switch out: ");
				fgets(switched_item_name,500,stdin);	/*takes in the name of the item being switched*/
				while(verifying_alpha(switched_item_name)==0){
                                        fgets(switched_item_name,500,stdin);
                                        verifying_alpha(switched_item_name);
                                }
				take_off(switched_item_name);
				while(current_item!=NULL){
					if(strcmp(switched_item_name,current_item->item_name)==0){/*traverses through the item list until it finds a matching name*/
						printf("Please enter what you would like to add instead: \n");
						fgets(c5,500,stdin);		/*takes in the item to be replaced*/
						while(verifying_alpha(c5)==0){
                                        		fgets(c5,500,stdin);
                                        		verifying_alpha(c5);
                                		}
						replaced_item_name=malloc(sizeof(char)*(strlen(c5)+1));
						sscanf(c5,"%[^\n]s",replaced_item_name);
						take_off(replaced_item_name);	
						free(current_item->item_name);	/*frees current_item's name before reassigning it with replaced_item_name*/
						current_item->item_name=replaced_item_name;
					}
					current_item=current_item->next_item;
				}
				sorted_list(current_order->order_list);
				printf("Ruff! (Switched an item out from your order!)\n");
				printf("\n");
			}		
			break;
		}
		prev_order=current_order;
		current_order=current_order->next_order;
	}
	return orderlist;
}
void merge_orders(order *orderlist){
	order *current_order;
	order *prev_order;
        order *nextorder;
        order *temp_order;
	current_order=orderlist;
	while(current_order!=NULL){	/*traverses through the orderlist*/
		prev_order=current_order;
		nextorder=current_order->next_order;
		while(nextorder!=NULL){	/*traverses through as long as current's next field isn't null*/
			if(strcmp(current_order->name,nextorder->name)==0){/*checks if current's name and nextorder's name are the same*/
				transfer_order_items(current_order,nextorder);/*calls transfer_order_items to add nextorder's items to current*/
				prev_order->next_order=nextorder->next_order;/*preserves nextorder's next field by setting it to prev_order's*/
				free(nextorder->order_list);
				free(nextorder->name);/*frees nextorder's fields before setting temp_order equal to it*/
				temp_order=nextorder;
				nextorder=nextorder->next_order;	/*nextorder moves forward to look for more matches*/
				free(temp_order);		
			}
			else{
				prev_order=nextorder;
				nextorder=nextorder->next_order;
			}
		}
		current_order=current_order->next_order;
	}
	printf("Bark! (Merging all orders with the same name!)\n");
	printf("\n");
}
void transfer_order_items(order *survivor, order *temporary){/*helper function that takes two orders and funnels one's items into the other*/
	item *temp_item;
	item *current_item=temporary->order_list->item;
	while(current_item!=NULL){
		temp_item=current_item;
		current_item=current_item->next_item;
		add_item(survivor->order_list,temp_item);	/*adds items from temporary into survivor*/
	}
	sorted_list(survivor->order_list);	/*alphabetically sorts survivor's items*/
}
void current_orders(order *orderlist){
	order *current_order=orderlist;
	int ordercounter=0;
	while(current_order!=NULL){
		ordercounter++;		/*adds up all the orders inside of orderlist*/
		current_order=current_order->next_order;
	}
	printf("There are currently %d order(s) which have been placed.\n",ordercounter);	/*prints out the number of orders being processed*/
	printf("\n");
}
