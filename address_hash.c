#include<stdio.h>
#include<stdlib.h>

#define HASH_SIZE	5381

struct list {
	struct r_list *r_node;
	struct r_list *new_node;
	struct list *next;
};
typedef struct list LIST;
LIST list_buffer[100000];
int list_buffer_count = 0;

LIST *hash_map[HASH_SIZE + 1] = {0};

struct r_list {
	int x;
	struct r_list *next;
	struct r_list *random;
};
typedef struct r_list RANDOM_LIST;
RANDOM_LIST random_list_buffer[100000];
int random_list_buffer_count = 0;


LIST *create_list_node(RANDOM_LIST *p, RANDOM_LIST *new_head)
{
	LIST *node;
	node = &list_buffer[list_buffer_count];
	node->r_node = p;
	node->new_node = new_head;
	node->next = NULL;
	list_buffer_count++;
	return(node);
}

RANDOM_LIST *create_random_list_node(int x)
{
	RANDOM_LIST *node;
	node = &random_list_buffer[random_list_buffer_count];
	node->x = x;
	node->next = NULL;
	node->random = NULL;
	random_list_buffer_count++;
	return(node);
}

void insert_in_list(LIST *head, LIST *new_node)
{
	if (!head) {
		head = new_node;
		return;
	}

	new_node->next = head->next;
	head = 	new_node;

}

void insert_in_hash_map(RANDOM_LIST *node, RANDOM_LIST *new_head)
{
	unsigned int address = (int )node;
	LIST *new_node;
#if 1
	printf("%s-%d --> %d\n", __func__, __LINE__, address%HASH_SIZE);
#endif
	new_node = create_list_node(node, new_head);
	insert_in_list(hash_map[address%HASH_SIZE], new_node);

}

RANDOM_LIST  *copy_random_list(RANDOM_LIST *head)
{
	RANDOM_LIST *temp = head;
	RANDOM_LIST *new_temp, *prev = NULL;
	RANDOM_LIST *new_head;
	int address;
	
	new_temp = create_random_list_node(temp->x);
	insert_in_hash_map(temp, new_temp);
	new_head = new_temp;
	while (temp->next) {
#ifdef DEBUG
		printf("%s-%d\n", __func__, __LINE__);
#endif
		new_temp->next = create_random_list_node(temp->next->x);
		temp = temp->next;
		insert_in_hash_map(temp, new_temp->next);
		new_temp = new_temp->next;
	}
	//prev->next = NULL;
	new_temp = new_head;
	while(new_temp) {
		printf("new_temp->x = %d\n", new_temp->x);
		new_temp = new_temp->next;
	}
	temp = head;
	new_temp = new_head;
	while (temp) {
		//search_in_hash_map();
		temp = temp->next;
	}
	return(new_head);
}

int main()
{
	unsigned long int address;
	int  x;
	int *p = &x;
	int i;
	address = (unsigned long int )p;
	printf("address of x = %p\n", p);
	printf("address of x = %p\n", &x);
	printf("adress = %lx\n", address);
	
	RANDOM_LIST *head,*last,*temp, *new_head;
	temp = create_random_list_node(1);
	head = temp;
	temp = create_random_list_node(2);
	head->next = temp;
	temp = create_random_list_node(3);
	head->next->next = temp;
	temp = create_random_list_node(4);
	head->next->next->next = temp;
#ifdef DEBUG
	printf("%s-%d\n", __func__, __LINE__);
#endif
	new_head = copy_random_list(head);
	
	//address = (int )l1;
	//printf("address of l1 = %p address = %x\n", l1, address);

	return 0;
}
